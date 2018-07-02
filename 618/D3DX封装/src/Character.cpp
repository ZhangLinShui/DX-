#include "StdAfx.h"
#include ".\character.h"
#include "SceneManager.h"
CCharacter::CCharacter(void) :
m_fMoveSpeed(0.0f),
m_vMax(0, 0, 0),
m_vMin(-0, 0.0f, -0)
{
	m_lType= OB_TYPE_MONSTER;

	m_dwCurrentTrack = 0;
	m_fTimeCurrent = 0;
}

CCharacter::~CCharacter(void)
{
	
}
BOOL CCharacter::Init(TiXmlElement* element)
{
	m_pDevice = (LPDIRECT3DDEVICE9)CPlatform::GetsinglenPtr()->FindResourceA("设备接口");

	TiXmlElement* childNode = element->FirstChildElement("Pos");
	m_vPos.x = atoi(childNode->Attribute("x"));
	m_vPos.y = atoi(childNode->Attribute("y"));
	m_vPos.z = atoi(childNode->Attribute("z"));
	childNode = element->FirstChildElement("Scale");
	int Scalex = atoi(childNode->Attribute("scalex"));
	int Scaley = atoi(childNode->Attribute("scaley"));
	int Scalez = atoi(childNode->Attribute("scalez"));
	childNode = element->FirstChildElement("BindMesh");
	Modedata = childNode->GetText();
	childNode = element->FirstChildElement("Roate");
	RoteX = atof(childNode->Attribute("x"));
	RoteY = atof(childNode->Attribute("y"));
	RoteZ = atof(childNode->Attribute("z"));
	Roate = atoi(childNode->GetText());

	m_pMultiAnim = (CMultiAnim*)CSceneManager::GetInstance()->GetObjectByName(Modedata);
	
	
	childNode = element->FirstChildElement("AnimationName");
	int aniID = atoi(childNode->GetText());
		HRESULT hr;
		

		hr = m_pMultiAnim->m_pAC->CloneAnimationController(m_pMultiAnim->m_pAC->GetMaxNumAnimationOutputs(),
			m_pMultiAnim->m_pAC->GetMaxNumAnimationSets(),
			m_pMultiAnim->m_pAC->GetMaxNumTracks(),
			m_pMultiAnim->m_pAC->GetMaxNumEvents(),
			&m_pAC);
		if (SUCCEEDED(hr))
		{
			DWORD i, dwTracks;
			dwTracks = m_pAC->GetMaxNumTracks();
			for (i = 0; i < dwTracks; ++i)
				m_pAC->SetTrackEnable(i, FALSE);

		}
		ChangeMotionType((enMotionType)aniID);


		D3DXMATRIX MatRot, MatSoll, MatT;
		D3DXMatrixRotationY(&MatRot, Roate);
		D3DXMatrixTranslation(&MatT, m_vPos.x, m_vPos.y, m_vPos.z);
		D3DXMatrixScaling(&MatSoll, Scalex, Scaley, Scalez);
		matWorld = MatSoll * MatRot*MatT;

		return true;
}


void CCharacter::Update(float fElapsedTime)
{
	/*if (m_enMotionType == MT_ATTACK || m_enMotionType == MT_BEHIT)
	if (GetPlayTime() > m_dwControlPlayTime)
	ChangeMotionType(MT_STAY);

	if (m_enMotionType == MT_DIEING && GetPlayTime() > 0)
	ChangeMotionType(MT_DEAD);*/	




}


void CCharacter::Draw()
{
	//SetmatWorld();
	AdvanceTime(0.05, nullptr, GetWorldMatrix());
	
	DrawFrames(m_pMultiAnim->m_pFrameRoot);
}



void CCharacter::ChangeMotionType(enMotionType enType)
{
	m_enMotionType = enType;

	switch (m_enMotionType)
	{
	case MT_STAY:
		SetAnimationByName("stand");
		break;

	case MT_WALK:
		SetAnimationByName("walking");
		break;

		/*case MT_ATTACK:
			SetAnimationByName("BeHit_left");
			break;

		case MT_BEHIT:
			SetAnimationByName("BeHit_right");
			break;

		case MT_DIEING:
			SetAnimationByName("Die");
			break;*/
	}
}




void CCharacter::SetAnimationByName(string name, DWORD dwControlPlayTime, bool bSmooth)
{
	if (m_strNowAnimationName == name)
		return;

	m_strNowAnimationName = name;

	//当前播放的次数
	m_dwPlayTime = 0;
	//当前已经播放的时间值
	m_fFrameTime = 0.0f;
	//想要播放的次数
	m_dwControlPlayTime = dwControlPlayTime;

	DWORD dwNewTrack = (m_dwCurrentTrack == 0 ? 1 : 0);
	LPD3DXANIMATIONSET pAS;
	m_pAC->GetAnimationSetByName(name.c_str(), &pAS);
	m_lfTotalFrameTime = pAS->GetPeriod();
	m_pAC->SetTrackPosition(dwNewTrack, 0);
	m_pAC->SetTrackAnimationSet(dwNewTrack, pAS);

	m_pAC->UnkeyAllTrackEvents(m_dwCurrentTrack);
	m_pAC->UnkeyAllTrackEvents(dwNewTrack);

	m_pAC->KeyTrackEnable(m_dwCurrentTrack, FALSE, m_fTimeCurrent + MOVE_TRANSITION_TIME);
	m_pAC->KeyTrackSpeed(m_dwCurrentTrack, 0.0f, m_fTimeCurrent, MOVE_TRANSITION_TIME, D3DXTRANSITION_LINEAR);
	m_pAC->KeyTrackWeight(m_dwCurrentTrack, 0.0f, m_fTimeCurrent, MOVE_TRANSITION_TIME, D3DXTRANSITION_LINEAR);
	m_pAC->SetTrackEnable(dwNewTrack, TRUE);
	m_pAC->KeyTrackSpeed(dwNewTrack, 1.0f, m_fTimeCurrent, MOVE_TRANSITION_TIME, D3DXTRANSITION_LINEAR);
	m_pAC->KeyTrackWeight(dwNewTrack, 1.0f, m_fTimeCurrent, MOVE_TRANSITION_TIME, D3DXTRANSITION_LINEAR);
	pAS->Release();
	m_dwCurrentTrack = dwNewTrack;
}

DWORD CCharacter::GetPlayTime()
{
	// 如果没有动画控制器，则默认播放了一次
	if (m_pAC == NULL)
		m_dwPlayTime = 1;

	return m_dwPlayTime;
}
//-----------------------------------------------------------------------------
// Name: CAnimInstance::UpdateFrame()
// Desc: Recursively walk the animation frame hierarchy and for each frame,
//       transform the frame by its parent, starting with a world transform to
//       place the mesh in world space.  This has the effect of a hierarchical
//       transform over all the frames.
//-----------------------------------------------------------------------------
void CCharacter::UpdateFrames(LPD3DXFRAME pFrame, D3DXMATRIX* pmxBase)
{
	//assert(pFrame != NULL);
	//assert(pmxBase != NULL);

	// transform the bone
	D3DXMatrixMultiply(&((D3DXFRAME_DERIVED*)pFrame)->CombinedTransformationMatrix,
		&pFrame->TransformationMatrix,
		pmxBase);

	// transform siblings by the same matrix
	if (pFrame->pFrameSibling)
		UpdateFrames(pFrame->pFrameSibling, pmxBase);

	// transform children by the transformed matrix - hierarchical transformation
	if (pFrame->pFrameFirstChild)
		UpdateFrames(pFrame->pFrameFirstChild,
			&((D3DXFRAME_DERIVED*)pFrame)->CombinedTransformationMatrix);
}

//-----------------------------------------------------------------------------
// Name: CAnimInstance::DrawFrames()
// Desc: Recursively walk the frame hierarchy and draw each mesh container as
//       we find it.
//-----------------------------------------------------------------------------
void CCharacter::DrawFrames(LPD3DXFRAME pFrame)
{
	if (pFrame->pMeshContainer)
		DrawMeshFrame(pFrame);

	if (pFrame->pFrameSibling)
		DrawFrames(pFrame->pFrameSibling);

	if (pFrame->pFrameFirstChild)
		DrawFrames(pFrame->pFrameFirstChild);
}


//-----------------------------------------------------------------------------
// Name: CAnimInstance::DrawMeshFrame()
// Desc: Renders a mesh container.  Here we go through each attribute group
//       and set up the matrix palette for each group by multiplying the
//       bone offsets to its bone transformation.  This gives us the completed
//       bone matrices that can be used and blended by the pipeline.  We then
//       set up the effect and render the mesh.
//-----------------------------------------------------------------------------
void CCharacter::DrawMeshFrame(LPD3DXFRAME p)
{
	HRESULT hr;
	D3DXMESHCONTAINER_DERIVED *pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)p->pMeshContainer;
	D3DXFRAME_DERIVED *pFrame = (D3DXFRAME_DERIVED*)p;
	UINT iMaterial;
	UINT iAttrib;

	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;
	m_pDevice->GetDeviceCaps(&d3dCaps);

	// 检测蒙皮是否存在
	if (pMeshContainer->pSkinInfo != NULL)
	{
		D3DXMATRIX  Identity;
		DWORD       cBones = pMeshContainer->pSkinInfo->GetNumBones();
		DWORD       iBone;
		PBYTE       pbVerticesSrc;
		PBYTE       pbVerticesDest;

		// 设置骨骼变换

		for (iBone = 0; iBone < cBones; ++iBone)
		{

			D3DXMatrixMultiply(&pMeshContainer->m_pBoneMatrices[iBone],                 // output
				&pMeshContainer->pBoneOffsetMatrices[iBone],
				pMeshContainer->ppBoneMatrixPtrs[iBone]);

		}

		//// 设置世界变换矩阵
		D3DXMATRIX matWorld;
		D3DXMatrixIdentity(&matWorld);

		(m_pDevice->SetTransform(D3DTS_WORLD, &matWorld));

		(pMeshContainer->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pbVerticesSrc));
		(pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, (LPVOID*)&pbVerticesDest));

		// 更新蒙皮模型
		pMeshContainer->pSkinInfo->UpdateSkinnedMesh(pMeshContainer->m_pBoneMatrices, NULL, pbVerticesSrc, pbVerticesDest);

		(pMeshContainer->pOrigMesh->UnlockVertexBuffer());
		(pMeshContainer->MeshData.pMesh->UnlockVertexBuffer());

		for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
		{
			/*if( strcmp( pMeshContainer->cTexFileName, HIGH_LIGHT_TEX_NAME ) == 0  ||
			strcmp( pMeshContainer->cTexFileName, BOUND_MESH_TEX_NAME ) == 0 )
			{
			continue;
			}*/

			(m_pDevice->SetMaterial(&(pMeshContainer->pMaterials[pMeshContainer->pAttributeTable[iAttrib].AttribId].MatD3D)));
			(m_pDevice->SetTexture(0, pMeshContainer->ppTextures[pMeshContainer->pAttributeTable[iAttrib].AttribId]));
			(pMeshContainer->MeshData.pMesh->DrawSubset(pMeshContainer->pAttributeTable[iAttrib].AttribId));
		}
	}
	//else  // 静态模型
	//{
	//	(m_pDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix)); 


	//	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//	m_pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	//	for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
	//	{
	//		/*if( strcmp( pMeshContainer->cTexFileName, HIGH_LIGHT_TEX_NAME ) == 0  ||
	//		strcmp( pMeshContainer->cTexFileName, BOUND_MESH_TEX_NAME ) == 0 )
	//		{
	//		continue;
	//		}*/

	//		(m_pDevice->SetMaterial(&pMeshContainer->pMaterials[iMaterial].MatD3D));
	//		(m_pDevice->SetTexture(0, pMeshContainer->ppTextures[iMaterial]));
	//		(pMeshContainer->MeshData.pMesh->DrawSubset(iMaterial));
	//	}
	//}
}




HRESULT CCharacter::AdvanceTime(DOUBLE dTimeDelta, ID3DXAnimationCallbackHandler* pCH, D3DXMATRIX mat)
{
	if (m_dwControlPlayTime == 0 || m_dwPlayTime < m_dwControlPlayTime)
		m_pAC->AdvanceTime(dTimeDelta, NULL);

	// 计算动画播放次数
	m_fTimeCurrent += dTimeDelta;
	m_fFrameTime += dTimeDelta;
	if (m_fFrameTime >= m_lfTotalFrameTime)
	{
		m_fFrameTime = 0.0f;
		m_dwPlayTime++;
	}

	// from root to leaf, calculate all absolute matrix
	/*	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);*/
	UpdateFrames(m_pMultiAnim->m_pFrameRoot, &mat);

	return S_OK;
}

