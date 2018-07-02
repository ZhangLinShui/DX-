
#pragma once

#include <vector>
#include <string>

#include "Object.h"
class CMultiAnim;
class CAnimInstance;

//-----------------------------------------------------------------------------
// Name: class CMultiAnimAllocateHierarchy
// Desc: Inheriting from ID3DXAllocateHierarchy, this class handles the
//       allocation and release of the memory used by animation frames and
//       meshes.  Applications derive their own version of this class so
//       that they can customize the behavior of allocation and release.
//-----------------------------------------------------------------------------
class CAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	/** 创建骨骼
	*/
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	/** 创建模型容器
	*/
	STDMETHOD(CreateMeshContainer)(THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer);
	/** 销毁骨骼
	*/
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
	/** 销毁模型容器
	*/
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);

	CAllocateHierarchy() {}

	CMultiAnim *m_pParent;
	
};


struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16        CombinedTransformationMatrix;		// absolute matrix
	D3DXMATRIX			 ExTransformationMatrix;			// 扩展变换矩阵(用于外界设置骨骼的变换，该矩阵与骨骼源矩阵相乘得到骨骼的最终变换矩阵)
};

struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;       // array of textures, entries are NULL if no texture specified
	std::vector<std::string> vecTexFileName;

	// 皮肤信息             
	LPD3DXMESH           pOrigMesh;
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD                NumAttributeGroups;
	DWORD                NumInfl;
	LPD3DXBUFFER         pBoneCombinationBuf;
	D3DXMATRIX**         ppBoneMatrixPtrs;
	D3DXMATRIX*          pBoneOffsetMatrices;
	D3DXMATRIX *		m_pBoneMatrices;
	DWORD                NumPaletteEntries;
	bool                 UseSoftwareVP;
	DWORD                iAttributeSW;
};





//-----------------------------------------------------------------------------
// Name: class CMultiAnim
// Desc: This class encapsulates a mesh hierarchy (typically loaded from an
//       .X file).  It has a list of CAnimInstance objects that all share
//       the mesh hierarchy here, as well as using a copy of our animation
//       controller.  CMultiAnim loads and keeps an effect object that it
//       renders the meshes with.
//-----------------------------------------------------------------------------
class CMultiAnim:public CObject
{
	friend class CAllocateHierarchy;
	friend class CAnimInstance;
	friend struct MultiAnimFrame;
	friend struct MultiAnimMC;

public:

	CAllocateHierarchy		m_Alloc;
	
	
	D3DXFRAME* m_pFrameRoot;           // shared between all instances
	LPD3DXANIMATIONCONTROLLER m_pAC;                  // AC that all children clone from -- to clone clean, no keys

private:

	HRESULT GenerateSkinnedMesh(D3DXMESHCONTAINER_DERIVED *pMeshContainer);
	HRESULT             SetupBonePtrs(D3DXFRAME* pFrame);
	HRESULT SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase);
	string m_TextruePath;
	string &m_() { return m_TextruePath; }
public:

	CMultiAnim();
	virtual             ~CMultiAnim();
	CAnimInstance*      CreateInstance();
	BOOL Init(TiXmlElement* element);
	virtual HRESULT     Cleanup(CAllocateHierarchy* pAH);
	
};

