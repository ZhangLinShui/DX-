#include "stdafx.h"
#include "SceneManager.h"

//��̬��Ա�ĳ�ʼ��
CSceneManager* CSceneManager::m_Instance = NULL;


//��ȡȫ��Ψһ�ĳ����������Ķ���
CSceneManager* CSceneManager::GetInstance()
{
	if (NULL == m_Instance)
	{
		m_Instance = new CSceneManager();
	}
	return m_Instance;
}

//���캯��
CSceneManager::CSceneManager()
{
	m_mapObject.clear();
	m_lNumOfObject = 0;
	m_ImapObject = new ImapObject();
	m_pDevice = NULL;
}

//��������
CSceneManager::~CSceneManager()
{
	Release();
}

//��ʼ������������
bool CSceneManager::Init(string fileName)
{
	TiXmlDocument curFile(fileName.c_str());
	string type;
	string name;

	if (curFile.LoadFile())
	{

		TiXmlElement *root = curFile.FirstChildElement("ObjectS");

		for (TiXmlElement * node = root->FirstChildElement("Obj"); node != NULL; node = node->NextSiblingElement("Obj"))
		{
			CObject* object = NULL;
			type = node->Attribute("Type");
			name = node->Attribute("Name");
			//�ж���������Ƿ��Ѿ�������
			if (m_mapObject.find(name) != m_mapObject.end())
			{
				return m_mapObject[name];
			}

			switch (atoi(type.c_str()))
			{
			case OB_TYPE_MAP:
				object = new CCMap();
				break;
			case OB_TYPE_PLAYER:
				object = new CPlayer();
				break;
			case OB_TYPE_CAMERA:
				object = new CCamera();
				break;
			case OB_TYPE_SKY:
				object = new CSky();
				break;
			case OB_TYPE_Light:
				//object = new CLight();
				break;
			case OB_TYPE_WATER:
				object = new CWater();
				break;
			case OB_TYPE_BRIDGE:
				object = new CBridge();
				break;
			case OB_TYPE_HOURSE:
				//object = new CHourse();
				break;
			case  OB_TYPE_MODEL:
				object = new CModel();
				break;
			case OB_TYPE_MODEL_COPY:
				object = new CModelCopy();
				break;
			case OB_TYPE_ANIMATION_MESH:
				object = new CMultiAnim();
				break;
			case OB_TYPE_MONSTER:
				object = new CCharacter();
				break;
				}
			if (object)
			{
				object->Init(node);
				m_mapObject[name] = object;
				m_lNumOfObject = (long)m_mapObject.size();
				m_ImapObject->ObjectName = name;
				m_ImapObject->Object = object;
				NotifyObserver((IObject*)m_ImapObject);

			}
		}
	}
	return true;
}


//�ͷų���������
void CSceneManager::Release()
{
	DestroyScene();
	m_mapObject.clear();
	SAFE_DELETE(m_ImapObject);
}


//����һ������
void CSceneManager::DestroyScene()
{
	for (map<string, CObject*>::iterator it = m_mapObject.begin(); it != m_mapObject.end(); ++it)
	{
		SAFE_DELETE(it->second);
	}
	m_mapObject.clear();
}


//����һ������
void CSceneManager::DestroyObject(string objectname)
{
	delete m_mapObject[objectname];
	SAFE_DELETE(m_mapObject[objectname]);
	SAFE_DELETE(m_mapObject.find(objectname)->second);

	if (!m_mapObject[objectname])
	{
		m_mapObject.erase(objectname);
	}

	m_lNumOfObject = (long)m_mapObject.size();

	m_ImapObject->ObjectName = objectname;
	m_ImapObject->Object = NULL;
	NotifyObserver(m_ImapObject);
}

CSceneManager* GetSceneMgr()
{
	return CSceneManager::GetInstance();
}
