#pragma once
#include "RenderObject.h"
#include "Model.h"

class CModelCopy :
	public CRenderObject
{
public:
	CModelCopy();
	~CModelCopy();
	BOOL Init(TiXmlElement* element);
	void Draw();
	D3DXMATRIX GetMatInverse();
	CModel* GetCModel();
	
	string					name;
	CModel*					m_pBindModle;
	
	D3DXMATRIX              m_matInverse;
	float					Scalex, Scaley, Scalez;
	float					RoteX, RoteY, RoteZ;
	float					TranslationX, TranslationY, TranslationZ, TranslationY1;
	bool					Roate;
	bool					Translation;
	bool					flag;//¿ØÖÆÉý½µ
	
};

