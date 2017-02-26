#ifndef _CHAT_H_
#define _CHAT_H_

#pragma  once
#include "object.h"
#include "chattype.h"
#include <time.h>
#include "sceneobj_define.h"
#include "scenecfg_manager.h"
//#define  SPEAKCOUNT  6
// ********************************************************************** //
// CChat
// ********************************************************************** //

class TimeLimit
{
 //enum { MAX_CHATMSG_LEN = 200 };
private:	

	time_t ChatTime;
	time_t FirMessTime;
	time_t SecMessTime;		
	char MessBuffer[ MAX_MASSAGE_LEN ];
	int  MessCount;	

private:	
	int  CheckMess( const char *pMess, int MessTime );
public:
	enum
	{
		SendOk = 1,				// ���Է���
		NotInTimeLimit = 2,		// ����Ƶ�ʹ���
		NotInMessLimit = 3,		// һ�仰6�����ظ�����
		INCOOLTIME	   = 4,		// ���ڿ�����߸յ�¼����������ȴʱ��
	};
public:	
	TimeLimit();	
	int Initialize();
	int Resume(); 
	int CanSendMess( const char *p, int ChatLimitTime, int MessLimitTime );
	int SetChatTime( int nChatTime, int nFirMsgTime, int nSecMsgTime );	
};




class CChat : public CObj
{
private:
	int mForbiddenChannel;	
	int mFreeTime; // ��ֹ����ʱ��(δ��ʱ��), ��λ: ��
	
	enum { InCommonTime,InPtoPTime,InWorldTime };
public:
	
	CChat(  )
	{
		if( CObj::msCreateMode )
		{
			Initialize();
		}
		else
		{
			Resume();
		}
	}

	virtual ~CChat() {};

	virtual int Initialize()
    {
		mForbiddenChannel = 0;
		mFreeTime = 0;
		return 0;
	}
	virtual int Resume() {return 0;}

	bool InChannel( CHAT_CHANNEL vChannel );	
	
	// ���ý���Ƶ��
	void SetChannel( int vChannel, bool IfSetChannelTrue = false );
	
	// ��ʼ������Ƶ��
	void InitialChannel( int vChannel, int nPeriod );
	
	// �õ�����Ƶ��
	int GetForbidenChannel( );
	
	// �õ����ʱ��
	inline int GetForbidenFreeTime( ) { return mFreeTime; }

	//ʱ�����ƴ���
	//TimeLimit PtoPTimeLimit;
	TimeLimit CommonTimeLimit;
	TimeLimit WorldTimeLimit;
	TimeLimit CounrtyTimeLimit;
	
	//ʱ�����ƴ���
	
};
struct sAutoMsg
{
	//char PlayerName[NAME_LENGTH];
	int  PlayerId;
	char MessBuff[ MAX_MASSAGE_LEN ];
	int  time;
	int  count;
	int  channel;
	sAutoMsg( )
	{
		if ( CObj::msCreateMode )
		{
			Initialize();
		}
		else
		{
			Resume();
		}
	}  
	int Initialize();
	int Resume();
} ;

class CAutoMsg
{
private:	  
	int mSpeakNum;          //����ʹ���Զ���������Ҹ���	
	int mCurChatPos;        //��ȡ�����е�ǰ���Է��Ե������Ϣ
    int mGetChatBegin;      //��־�Ƿ���ѭ����ȡ�����������ݵĹ�����
	sAutoMsg mDeletedChat;  //�������һ�α�ɾ���������Ϣ
public:
	 sAutoMsg mAutoMessBuff[ MAXAUTOCHATNUM ];
	 enum 
	 {
		 CHATCOMPLETE = 1,    //��ɺ�������һ��ѭ�����
		 CURCHATNOTINTIME,    //���������еĵ�ǰ���δ������ʱ��
		 CURCHATINTIME,        //���������е�ǰ�������ʱ��Ҫ����Է���
		 CURCHATCOMPLETE      //��ǰ��ҵ��Զ������Ѿ�����
	 };
public:  
  
   void SetCurPos( int pos = 0 );

   int InsertAutoMess(  int playerid, const char *pMess, int time, int channel, int chatcount );

   int GetCurrentChat( sAutoMsg *CurAutoChat);

   int ModifyAutoMess( int playerid, const char *pMess, int time, int channel, int chatcount = 1 );

   int DelAutoMess( int playerid, int iscurrentplayer = 1 );

   int ChangeChatCount( int playerid, int count ) ;
   
   int GetSpeakNum( );    

public:
   CAutoMsg( );
   int Initialize();
   int Resume();
   ~CAutoMsg( ){ };  
};
#endif


