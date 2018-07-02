#include "stdafx.h"
#include "MultiAnim.h"


/** 给框架或模型名的字符串分配空间
*/
HRESULT AllocateName(LPCSTR Name, LPSTR *pNewName)
{
	UINT cbLength;

	if (Name != NULL)
	{
		cbLength = (UINT)strlen(Name) + 1;
		*pNewName = new CHAR[cbLength];
		if (*pNewName == NULL)
			return E_OUTOFMEMORY;
		memcpy(*pNewName, Name, cbLength * sizeof(CHAR));
	}
	else
	{
		*pNewName = NULL;
	}

	return S_OK;
}


HRESULT CAllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame)
{
	HRESULT hr = S_OK;
	D3DXFRAME_DERIVED *pFrame;

	*ppNewFrame = NULL;

	pFrame = new D3DXFRAME_DERIVED;
	if (pFrame == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}

	hr = AllocateName(Name, &pFrame->Name);
	if (FAILED(hr))
		goto e_Exit;

	// 初始化骨骼其他数据成员 
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
	D3DXMatrixIdentity(&pFrame->ExTransformationMatrix);

	pFrame->pMeshContainer = NULL;
	pFrame->pFrameSibling = NULL;
	pFrame->pFrameFirstChild = NULL;

	*ppNewFrame = pFrame;
	pFrame = NULL;

e_Exit:
	delete pFrame;
	return hr;
}




//--------------------------------------------------------------------------------------
// Name: CAllocateHierarchy::CreateMeshContainer()
// Desc: 
//--------------------------------------------------------------------------------------
HRESULT CAllocateHierarchy::CreateMeshContainer(
	LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	HRESULT hr;
	D3DXMESHCONTAINER_DERIVED *pMeshContainer = NULL;
	UINT NumFaces;
	UINT iMaterial;
	UINT iBone, cBones;
	LPDIRECT3DDEVICE9 pd3dDevice = NULL;

	LPD3DXMESH pMesh = NULL;

	*ppNewMeshContainer = NULL;

	// this sample does not handle patch meshes, so fail when one is found
	if (pMeshData->Type != D3DXMESHTYPE_MESH)
	{
		hr = E_FAIL;
		goto e_Exit;
	}

	// get the pMesh interface pointer out of the mesh data structure
	pMesh = pMeshData->pMesh;

	// this sample does not FVF compatible meshes, so fail when one is found
	if (pMesh->GetFVF() == 0)
	{
		hr = E_FAIL;
		goto e_Exit;
	}

	// allocate the overloaded structure to return as a D3DXMESHCONTAINER
	pMeshContainer = new D3DXMESHCONTAINER_DERIVED;
	if (pMeshContainer == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}
	memset(pMeshContainer, 0, sizeof(D3DXMESHCONTAINER_DERIVED));

	// make sure and copy the name.  All memory as input belongs to caller, interfaces can be addref'd though
	hr = AllocateName(Name, &pMeshContainer->Name);
	if (FAILED(hr))
		goto e_Exit;

	pMesh->GetDevice(&pd3dDevice);
	NumFaces = pMesh->GetNumFaces();

	// if no normals are in the mesh, add them
	if (!(pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

		// clone the mesh to make room for the normals
		hr = pMesh->CloneMeshFVF(pMesh->GetOptions(),
			pMesh->GetFVF() | D3DFVF_NORMAL,
			pd3dDevice, &pMeshContainer->MeshData.pMesh);
		if (FAILED(hr))
			goto e_Exit;

		// get the new pMesh pointer back out of the mesh container to use
		// NOTE: we do not release pMesh because we do not have a reference to it yet
		pMesh = pMeshContainer->MeshData.pMesh;

		// now generate the normals for the pmesh
		D3DXComputeNormals(pMesh, NULL);
	}
	else  // if no normals, just add a reference to the mesh for the mesh container
	{
		pMeshContainer->MeshData.pMesh = pMesh;
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

		pMesh->AddRef();
	}

	// allocate memory to contain the material information.  This sample uses
	//   the D3D9 materials and texture names instead of the EffectInstance style materials
	pMeshContainer->NumMaterials = fmax<int>(1, NumMaterials);
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	pMeshContainer->pAdjacency = new DWORD[NumFaces * 3];
	if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
	{
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}

	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * NumFaces * 3);
	memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	// if materials provided, copy them
	if (NumMaterials > 0)
	{
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

		for (iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
		{
			if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
			{
				string strPath = m_pParent->m_TextruePath;
				string strTexName = pMeshContainer->pMaterials[iMaterial].pTextureFilename;

				strPath += strTexName;
				{
					if (FAILED(D3DXCreateTextureFromFile(pd3dDevice, strPath.c_str(),
						&pMeshContainer->ppTextures[iMaterial])))
						pMeshContainer->ppTextures[iMaterial] = NULL;
				}

				// don't remember a pointer into the dynamic memory, just forget the name after loading
				//strcpy(pMeshContainer->cTexFileName, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
				pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
			}
		}
	}
	else // if no materials provided, use a default one
	{
		pMeshContainer->pMaterials[0].pTextureFilename = NULL;
		memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
	}

	// if there is skinning information, save off the required data and then setup for HW skinning
	if (pSkinInfo != NULL)
	{
		// first save off the SkinInfo and original mesh data
		pMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		pMeshContainer->pOrigMesh = pMesh;
		pMesh->AddRef();

		// Will need an array of offset matrices to move the vertices from the figure space to the bone's space
		cBones = pSkinInfo->GetNumBones();
		pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[cBones];
		if (pMeshContainer->pBoneOffsetMatrices == NULL)
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}

		// get each of the bone offset matrices so that we don't need to get them later
		for (iBone = 0; iBone < cBones; iBone++)
		{
			pMeshContainer->pBoneOffsetMatrices[iBone] = *(pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
		}



		// fill meshcontainer 's skin info.
		// GenerateSkinnedMesh will take the general skinning information and transform it to a HW friendly version
		hr = m_pParent->GenerateSkinnedMesh( pMeshContainer);
		if (FAILED(hr))
			goto e_Exit;
	}

	*ppNewMeshContainer = pMeshContainer;
	pMeshContainer = NULL;

e_Exit:
	SAFE_RELEASE(pd3dDevice);

	// call Destroy function to properly clean up the memory allocated 
	if (pMeshContainer != NULL)
	{
		DestroyMeshContainer(pMeshContainer);
	}

	return hr;
}




//--------------------------------------------------------------------------------------
// Name: CAllocateHierarchy::DestroyFrame()
// Desc: 
//--------------------------------------------------------------------------------------
HRESULT CAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	SAFE_DELETE_ARRAY(pFrameToFree->Name);
	SAFE_DELETE(pFrameToFree);
	return S_OK;
}




//--------------------------------------------------------------------------------------
// Name: CAllocateHierarchy::DestroyMeshContainer()
// Desc: 
//--------------------------------------------------------------------------------------
HRESULT CAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	UINT iMaterial;
	D3DXMESHCONTAINER_DERIVED *pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

	SAFE_DELETE_ARRAY(pMeshContainer->Name);
	SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
	SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
	SAFE_DELETE_ARRAY(pMeshContainer->pBoneOffsetMatrices);

	// release all the allocated textures
	if (pMeshContainer->ppTextures != NULL)
	{
		for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			SAFE_RELEASE(pMeshContainer->ppTextures[iMaterial]);
		}
	}

	SAFE_DELETE_ARRAY(pMeshContainer->ppTextures);
	SAFE_DELETE_ARRAY(pMeshContainer->ppBoneMatrixPtrs);
	SAFE_RELEASE(pMeshContainer->pBoneCombinationBuf);
	SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
	SAFE_RELEASE(pMeshContainer->pSkinInfo);
	SAFE_RELEASE(pMeshContainer->pOrigMesh);
	SAFE_DELETE_ARRAY(pMeshContainer->pAttributeTable);
	SAFE_DELETE(pMeshContainer);
	return S_OK;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CMultiAnim::CMultiAnim() :m_pFrameRoot(NULL),
m_pAC(NULL)
{
	m_Alloc.m_pParent = (this);
}




//-----------------------------------------------------------------------------
// Name: CMultiAnim::~CMultiAnim()
// Desc: Destructor for CMultiAnim
//-----------------------------------------------------------------------------
CMultiAnim::~CMultiAnim()
{

}



//-----------------------------------------------------------------------------
// Name: CMultiAnim::Setup()
// Desc: The class is initialized with this method.
//       We create the effect from the fx file, and load the animation mesh
//       from the given X file.  We then call SetupBonePtrs() to initialize
//       the mesh containers to enable bone matrix lookup by index.  The
//       Allocation Hierarchy is passed by pointer to allow an app to subclass
//       it for its own implementation.
//-----------------------------------------------------------------------------
BOOL CMultiAnim::Init(TiXmlElement* element)
{
	m_pDevice = (LPDIRECT3DDEVICE9)CPlatform::GetsinglenPtr()->FindResourceA("设备接口");
	TiXmlElement*childNode = element->FirstChildElement("Mesh");
	string  name = childNode->GetText();

	childNode = element->FirstChildElement("Path");
	m_TextruePath = (childNode->GetText());
	
	HRESULT hr;
	hr = D3DXLoadMeshHierarchyFromX(name.c_str(),
		D3DXMESH_MANAGED,
		m_pDevice,
		&m_Alloc,
		0,
		&m_pFrameRoot,
		&m_pAC);
	
	if (FAILED(hr))
		goto e_Exit;

	if (!m_pAC)
	{
		hr = E_FAIL;
		MessageBox(NULL,
			"The sample is attempting to load a mesh without animation or incompatible animation.  This sample requires tiny_4anim.x or a mesh with identical animation sets.  The program will now exit.",
			"Mesh Load Error", MB_OK);
		goto e_Exit;
	}

	// set up bone pointers
	hr = SetupBonePtrs(m_pFrameRoot);
	if (FAILED(hr))
		goto e_Exit;


e_Exit:

	if (FAILED(hr))
	{

		if (m_pAC)
		{
			m_pAC->Release();
			m_pAC = NULL;
		}

		if (m_pFrameRoot)
		{
			D3DXFrameDestroy(m_pFrameRoot, &m_Alloc);
			m_pFrameRoot = NULL;
		}
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	
	return hr;
}



//-----------------------------------------------------------------------------
// Name: CMultiAnim::Cleanup()
// Desc: Performs clean up work and free up memory.
//-----------------------------------------------------------------------------
HRESULT CMultiAnim::Cleanup(CAllocateHierarchy* pAH)
{

	if (m_pAC)
	{
		m_pAC->Release();
		m_pAC = NULL;
	}

	if (m_pFrameRoot)
	{
		D3DXFrameDestroy(m_pFrameRoot, pAH);
		m_pFrameRoot = NULL;
	}

	return S_OK;
}


HRESULT CMultiAnim::SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	UINT iBone, cBones;
	D3DXFRAME_DERIVED *pFrame;

	D3DXMESHCONTAINER_DERIVED *pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

	// 当蒙皮存在时设定骨骼变换矩阵 
	if (pMeshContainer->pSkinInfo != NULL)
	{
		cBones = pMeshContainer->pSkinInfo->GetNumBones();

		pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[cBones];
		if (pMeshContainer->ppBoneMatrixPtrs == NULL)
			return E_OUTOFMEMORY;

		for (iBone = 0; iBone < cBones; iBone++)
		{
			pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(iBone));
			if (pFrame == NULL)
				return E_FAIL;

			pMeshContainer->ppBoneMatrixPtrs[iBone] = &pFrame->CombinedTransformationMatrix;
		}
	}

	return S_OK;
}



//-----------------------------------------------------------------------------
// Name: CMultiAnim::CreateInstance()
// Desc: Create a new animation instance based on our animation frames and
//       animation controller.
//-----------------------------------------------------------------------------
CAnimInstance* CMultiAnim::CreateInstance()
{
//	LPD3DXANIMATIONCONTROLLER pNewAC = NULL;
//	HRESULT hr;
//	CAnimInstance* pAI = NULL;
//
//	// Clone the original AC.  This clone is what we will use to animate
//	// this mesh; the original never gets used except to clone, since we
//	// always need to be able to add another instance at any time.
//	hr = m_pAC->CloneAnimationController(m_pAC->GetMaxNumAnimationOutputs(),
//		m_pAC->GetMaxNumAnimationSets(),
//		m_pAC->GetMaxNumTracks(),
//		m_pAC->GetMaxNumEvents(),
//		&pNewAC);
//	if (SUCCEEDED(hr))
//	{
//		// create the new AI
//		pAI = new CAnimInstance(this);
//		if (pAI == NULL)
//		{
//			hr = E_OUTOFMEMORY;
//			goto e_Exit;
//		}
//		// set it up
//		hr = pAI->Setup(pNewAC);
//		if (FAILED(hr))
//			goto e_Exit;
//
//		return pAI;
//	}
//
//e_Exit:
//
//	if (FAILED(hr))
//	{
//		if (pAI)
//			delete pAI;
//
//		if (pNewAC)
//			pNewAC->Release();
//	}

	return NULL;
}

HRESULT CMultiAnim::GenerateSkinnedMesh(D3DXMESHCONTAINER_DERIVED *pMeshContainer)
{
	HRESULT hr = S_OK;
	D3DCAPS9 d3dCaps;
	
	m_pDevice->GetDeviceCaps(&d3dCaps);
	if (pMeshContainer->pSkinInfo == NULL)
		return hr;
	SAFE_RELEASE(pMeshContainer->MeshData.pMesh);//	SAFE_RELEASE( pMeshContainer->pBoneCombinationBuf );
	hr = pMeshContainer->pOrigMesh->CloneMeshFVF(D3DXMESH_MANAGED, pMeshContainer->pOrigMesh->GetFVF(),
		m_pDevice, &pMeshContainer->MeshData.pMesh);
	if (FAILED(hr))
		goto e_Exit;
	hr = pMeshContainer->MeshData.pMesh->GetAttributeTable(NULL, &pMeshContainer->NumAttributeGroups);
	if (FAILED(hr))
		goto e_Exit;
	delete[] pMeshContainer->pAttributeTable;
	pMeshContainer->pAttributeTable = new D3DXATTRIBUTERANGE[pMeshContainer->NumAttributeGroups];
	if (pMeshContainer->pAttributeTable == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}
	hr = pMeshContainer->MeshData.pMesh->GetAttributeTable(pMeshContainer->pAttributeTable, NULL);
	if (FAILED(hr))
		goto e_Exit;
	
		// 为混合矩阵申请空间
	/*if(pMeshContainer->m_pBoneMatrices)
		delete[] pMeshContainer->m_pBoneMatrices;*/
	pMeshContainer->m_pBoneMatrices = new D3DXMATRIX[pMeshContainer->pSkinInfo->GetNumBones()];
		if (pMeshContainer->m_pBoneMatrices == NULL)
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}

		//m_pDevice->Release();
e_Exit:
	return hr;
}


//-----------------------------------------------------------------------------
// Name: CMultiAnim::SetupBonePtrs()
// Desc: Recursively initialize the bone pointers for all the mesh
//       containers in the hierarchy.
//-----------------------------------------------------------------------------
HRESULT CMultiAnim::SetupBonePtrs(D3DXFRAME* pFrame)
{
	//assert(pFrame != NULL);

	HRESULT hr;

	if (pFrame->pMeshContainer != NULL)
	{
		hr = SetupBoneMatrixPointersOnMesh(pFrame->pMeshContainer);
		if (FAILED(hr))
			return hr;
	}

	if (pFrame->pFrameSibling)
	{
		// recursive call
		hr = SetupBonePtrs(pFrame->pFrameSibling);
		if (FAILED(hr))
			return hr;
	}

	if (pFrame->pFrameFirstChild)
	{
		// recursive call
		hr = SetupBonePtrs(pFrame->pFrameFirstChild);
		if (FAILED(hr))
			return hr;
	}

	return S_OK;
}
