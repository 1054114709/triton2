#ifndef _SERVERTOOL_H_
#define _SERVERTOOL_H_


#include <stdlib.h>
#include "object.h"
#include <algorithm>
#include <time.h>


#ifndef ARRAY_CNT
#define ARRAY_CNT(a)	( sizeof(a) / sizeof(a[0]))
#endif

// ����һ��0-x��Χ�ڵ������,������x
#define RAND(x) (int)( ( x )*(rand( )/(float)( RAND_MAX + 1.0 ) ))

#define _COUNTRY_NAME_LEN_  (32)
#define _COUNTRY_COUNT_MAX_ (10)


#define REPE_MAP_COUNT_MAX      ( 50 )

// �����ȼ����
enum REPE_LEVEL
{
	REPE_LEVEL_AVER	=	0,
	REPE_LEVEL_MAX	=	1,
	REPE_LEVEL_MIN	=	2
};


typedef unsigned long long KEY_TYPE;
#define INVITED_KEY_VALUE       			( 0 )
#define GetTimeFromKey( vKey )      		( ( int )( vKey & 0x00000000FFFFFFFF )
#define GetParameFromKey( vKey )			( ( int )( vKey >> 56 ) )


#define _SELF_SERVER_LINE_ID_					( 0 )
#define _NATIONALITY_LINE_ID_					( 100 )

// ս���ȴ��ȼ��б�������
#define WAIT_LIST_MAX               20
// �����ȼ��λ���������
#define LEVEL_SEGMENT_MAX			20

// ��ϢID����ģ��
// 0 11111 0 000000000 = 0x7E00
#define REGION_OF_MESSAGE( message_id )  ( message_id & 0x7C00 )


enum CREATE_TYPE
{
    CREATE_COMM             =   0,
    CREATE_SPECIAL_TIME     =   1,
};


struct CountryArrary
{
	char    mName[ _COUNTRY_NAME_LEN_ + 1 ];
};

class CWTSize;
class CWTPoint;
class CWTRect;

//! CWTSize ��
/*!
	CWTSize �Ƚ����� MFC CSize, ʵ�����������  mCX �� mCY ��Ա�ǹ����ģ�����
	CWTSize �ṩ��ά�����������ݵĳ�Ա����
*/
class CWTSize
{
public:
	int	mCX;			//! ������
	int	mCY;			//! ������

public:
	//! CWTSize ���캯��, Ĭ�Ϲ���һ�� CWTSize( 0, 0 ) ����
	CWTSize( ) : mCX( 0 ), mCY( 0 )						{	}

	//! CWTSize ���캯��, ͨ��������������һ�� CWTSize ����
	/*! \param int vCX ������
        \param int vCY ������ */
	CWTSize( int vCX, int vCY ) : mCX( vCX ), mCY( vCY )	{	}

public:
	//! CWTSize ���캯��
	~CWTSize( )											{	}

public:
	//! != ������, �ж�����CWTSize�Ƿ�һ��
    /*! \param const CWTSize& rSize  ��������
		\return ����ö����rSize��һ������true, ���򷵻�false */
	bool operator != ( const CWTSize& rSize ) const			
		{ return mCX != rSize.mCX || mCY != rSize.mCY; }

	//! == ������, �ж�����CWTSize�Ƿ�һ��
    /*! \param rSize CWTSize ��������
		\return ����ö����rSizeһ������true, ���򷵻�false */
	bool operator == ( const CWTSize& rSize ) const			
		{ return mCX == rSize.mCX && mCY == rSize.mCY; }

	//! -= ������, ��CWTSize�����ȥһ��CWTSize����
    /*! \param rSize CWTSize ��������
		\return û�з���ֵ */
	void operator -= ( const CWTSize& rSize )
		{ mCX -= rSize.mCX; mCY -= rSize.mCY; }

	//! += ������, ��CWTSize�������һ��rSize����
    /*! \param rSize CWTSize ��������
		\return û�з���ֵ */
	void operator += ( const CWTSize& rSize )
		{ mCX += rSize.mCX; mCY += rSize.mCY; }

	//! - ������, �����������rPoint��ֵ��ȥ��CWTSize�����ֵ
    /*! \param rSize CWTPoint ��������
		\return ����rPoint��ֵ��ȥ��CWTSize�����ֵ */
	CWTPoint operator - ( const CWTPoint& rPoint ) const;

	//! - ������, �����������rRect��ֵ��ȥ��CWTSize�����ֵ
    /*! \param rRect CWTRect ��������
		\return ����rRect��ֵ��ȥ��CWTSize����󣬹����CWTRect���� */
	CWTRect operator - ( const CWTRect& rRect ) const;
		
	//! - ������, ����������ظ�CWTSize�����ֵ��ȥCWTSize����󣬹����CWTSize���� */
    /*! \param rSize CWTSize ��������
		\return ���ظ�CWTSize�����ֵ��ȥ rSize��ֵ */
	CWTSize operator - ( const CWTSize& rSize ) const
		{ return CWTSize( mCX - rSize.mCX, mCY - rSize.mCY ); }

	//! - ������, ����������ظ�CWTSize�����ȡ���󣬹����CWTSize����
    /*! \return ���ظ�CWTSize����ȡ�����ֵ */
	CWTSize operator - ( ) const
		{ return CWTSize( -mCX, -mCY ); }

	//! + ������, �����������rPoint��ֵ���ϸ�CWTSize�����ֵ
    /*! \param rPoint CWTPoint ��������
		\return ����rPoint��ֵ���ϸ�CWTSize����󣬹����CWTPoint���� */
	CWTPoint operator + ( const CWTPoint& rPoint ) const;

	//! + ������, �����������rRect��ֵ���ϸ�CWTSize�����ֵ
    /*! \param rRect CWTRect ��������
		\return ����rRect��ֵ���ϸ�CWTSize����󣬹����CWTRect���� */
	CWTRect operator + ( const CWTRect& rRect ) const;

	//! + ������, ����������ظ�CWTSize�����ֵ����rSize�󣬹����CWTSize����
    /*! \param rSize CWTSize ��������
		\return ���ظ�CWTSize�������һ��rSize����󣬹����CWTSize���� */
	CWTSize operator + ( const CWTSize& rSize ) const
		{ return CWTSize( mCX + rSize.mCX, mCY + rSize.mCY ); }
};

//! CWTPoint ��
/*!
	CWTPoint �Ƚ����� MFC CPoint, ʵ�����������  mX �� mY ��Ա�ǹ����ģ�����
	CWTPoint �ṩ��ά�����������ݵĳ�Ա����
*/
class CWTPoint
{
public:
	int		mX;
	int		mY;

public:
	//! CWTPoint ���캯��, Ĭ�Ϲ���һ�� CWTPoint( 0, 0 ) ����
	CWTPoint( ) { }//: mX( 0 ), mY( 0 )						{	}
	//! CWTPoint ���캯��, ͨ��������������һ�� CWTPoint ����
	/*! \param vX int ��, ������
        \param vY int ��, ������ */
	CWTPoint( int vX, int vY ) : mX( vX ), mY( vY )	{	}
public:
	//! CWTPoint ���캯��
	~CWTPoint( )										{	}

public:
	//! ��Ա���� Offset, �������������ֱ����vXOffset, vYOffset
	/*! \param vX int ��, ������ƫ����
		\param vY int ��, ������ƫ���� */
	void Offset( int vXOffset, int vYOffset )
		{ mX += vXOffset; mY += vYOffset; }

	//! ��Ա���� Offset, �������������ֱ����rPoint.mX, rPoint.mY
    /*! \param rPoint const CWTPoint������, �洢�˺���������ƫ���� */
	void Offset( const CWTPoint& rPoint )
		{ mX += rPoint.mX; mY += rPoint.mY; }

	//! ��Ա���� Offset, �������������ֱ�ƫ��rSize.mX, rSize.mY */
    /*! \param rSize const CWTSize������, �洢�˺���������ƫ���� */
	void Offset( const CWTSize& rSize )
		{ mX += rSize.mCX; mY += rSize.mCY; }
	
	void Clear( ) { mX = -1; mY = -1; }

	//! ��Ա���� LimitDistance, �ж�Ŀ����뱾������Ƿ���vAmbit��
	bool LimitDistance( const CWTPoint& rDesPos, unsigned int vAmbit )
	{	
//		CWTPoint tLength = *this - rDesPos;
//		return tLength.mX * tLength.mX + tLength.mY * tLength.mY;
		if( (unsigned int )abs( mX - rDesPos.mX ) > vAmbit )
		{
			return false;
		}
		else if( ( unsigned int )abs( mY - rDesPos.mY ) > vAmbit )
		{
			return false;
		}

		return true;
	}

	int Length( const CWTPoint& rDesPos )
	{
		return std::max( abs( mY - rDesPos.mY ), abs( mX - rDesPos.mX ) );
	}
public:
	//! != ������, �ж�����CWTPoint�Ƿ�һ�� */
    /*! \param rPoint const CWTPoint������
		\return ����ö����rPoint��һ������true, ���򷵻�false */
	bool operator != ( const CWTPoint& rPoint ) const
		{ return mX != rPoint.mX || mY != rPoint.mY; }

	//! == ������, �ж�����CWTPoint�Ƿ�һ�� */
    /*! \param rPoint const CWTPoint������
		\return ����ö����rPointһ������true, ���򷵻�false */
	bool operator == ( const CWTPoint& rPoint ) const
		{ return mX == rPoint.mX && mY == rPoint.mY; }

	//! += ������, �ò�������һ��CWTSize���� */
    /*! \param rSize const CWTSize������
		\return û�з���ֵ */
	void operator += ( const CWTSize& rSize )
		{ mX += rSize.mCX; mY += rSize.mCY; }

	//! += ������, �ò�������һ��CWTPoint���� */
    /*! \param rPoint const CWTPoint������
		\return û�з���ֵ */
	void operator += ( const CWTPoint& rPoint )
		{ mX += rPoint.mX; mY += rPoint.mY; }

	//! -= ������, �ò�����ȥһ��CWTSize���� */
    /*! \param rSize const CWTSize������
		\return û�з���ֵ */
	void operator -= ( const CWTSize& rSize )
		{ mX -= rSize.mCX; mY -= rSize.mCY; }

	//! -= ������, �ò�����ȥһ��CWTPoint���� */
    /*! \param rPoint const CWTPoint������
		\return û�з���ֵ */
	void operator -= ( const CWTPoint& rPoint )
		{ mX -= rPoint.mX; mY -= rPoint.mY; }

	//! - ������, �ò������ظ�CWTPoint�����ȥһ��CWTPoint����󣬹����CWTPoint���� */
    /*! \param rPoint const CWTPoint������
		\return ���ظ�CWTPoint�����ȥһ��CWTPoint����󣬹����CWTPoint���� */
	CWTPoint operator - ( const CWTPoint& rPoint ) const
		{ return CWTPoint( mX - rPoint.mX, mY - rPoint.mY ); }

	//! - ������, �ò������ظ�CWTPoint�����ȥһ��CWTSize����󣬹����CWTPoint����
    /*! \param rSize const CWTSize������
		\return ���ظ�CWTPoint�����ȥһ��CWTSize����󣬹����CWTPoint���� */
	CWTPoint operator - ( const CWTSize& rSize ) const
		{ return CWTPoint( mX - rSize.mCX, mY - rSize.mCY ); }

	//! - ������, �ò�������CWTRect�����ȥ��CWTPoint����󣬹����CWTRect����
    /*! \param rRect const CWTRect������
		\return ����CWTRect�����ȥ��CWTPoint����󣬹����CWTRect���� */
	CWTRect operator - ( const CWTRect& rRect ) const;

	//! - ������, �ò������ظ�CWTPoint����ȡ���󣬹����CWTPoint����
    /*! \return ���ظ�CWTPoint����ȡ���󣬹����CWTPoint���� */
	CWTPoint operator - ( ) const
		{ return CWTPoint( -mX, -mY ); }

	//! + ������, �ò������ظ�CWTPoint�������һ��CWTPoint����󣬹����CWTPoint����
    /*! \param rPoint const CWTPoint������
		\return ���ظ�CWTPoint�������һ��CWTPoint����󣬹����CWTPoint���� */
	CWTPoint operator + ( const CWTPoint& rPoint ) const
		{ return CWTPoint( mX + rPoint.mX, mY + rPoint.mY ); }

	//! + ������, �ò������ظ�CWTPoint�������һ��CWTSize����󣬹����CWTPoint����
    /*! \param rSize const CWTSize������
		\return ���ظ�CWTPoint�������һ��CWTSize����󣬹����CWTPoint���� */
	CWTPoint operator + ( const CWTSize& rSize ) const
		{ return CWTPoint( mX + rSize.mCX, mY + rSize.mCY ); }

	//! + ������, �ò�������CWTRect������ϸ�CWTPoint����󣬹����CWTRect����
    /*! \param rRect const CWTRect������
		\return ����CWTRect������ϸ�CWTPoint����󣬹����CWTRect���� */
	CWTRect operator + ( const CWTRect& rRect ) const;
};

//! CWTRect ��
/*!
	CWTRect �Ƚ����� MFC CWTRect, ʵ������Ծ�������  mTopLeft �� mBottomRight ��Ա�ǹ����ģ�����
	CWTRect �ṩ��ά�����������ݵĳ�Ա����, CWTRect�Ĺ��캯��Ĭ�Ͻ�����NormalizeRect, �ú�����ʹ
	��һ��CWTRect����������, ����:mTopLeft( 10, 10 ) �� mBottomRight( 20, 20 )��һ�������ľ���, ��
	һ��mTopLeft( 20, 20 ) �� mBottomRight( 10, 10 )��һ���������ľ���, NormalizeRect��ʹ�������ľ�
	����������һ���������ľ�����ʹ��ĳЩCWTRect�ĳ�Ա����ʱ���ܻᷢ������
*/
class CWTRect
{
public:
	CWTPoint	mTopLeft;					//! CWTPoint ��,���ε����Ͻ�
	CWTPoint	mBottomRight;				//! CWTPoint ��,���ε����½�

public:
	//! CWTRect ���캯��, Ĭ�Ϲ���һ�� CWTRect( 0, 0, 0, 0 ) ����
	CWTRect( )	{ NormalizeRect( ); }

	//! \brief CWTRect ���캯��, ͨ��4���������� CWTRect ����, 
	/*! \param vLeft int �� ���ϽǺ�����
		\param vTop int �� ���Ͻ�������
		\param vRight int �� ���½Ǻ�����
		\param vBottom int �� ���½�������
		\param vNormalize bool �� �ǲ���Ҫ�������� CWTRect ���� 
		\sa CWTRect */
	CWTRect( int vLeft, int vTop, int vRight, int vBottom, bool vNormalize = true ) : mTopLeft( vLeft, vTop ), mBottomRight( vRight, vBottom )
		{ if ( vNormalize ) NormalizeRect( ); }

	//! CWTRect ���캯��, ͨ��1�� CWTPoint ��һ�� CWTSize ���� CWTRect ����, 
	/*! \param rPoint const CWTPoint ������ ���Ͻ�����
		\param rSize const CWTSize ������ CWTRect�ߴ�
		\param vNormalize bool �� �ǲ���Ҫ�������� CWTRect ���� 
		\sa CWTRect */
	CWTRect( const CWTPoint& rPoint, const CWTSize& rSize, bool vNormalize = true ) : mTopLeft( rPoint ), mBottomRight( rPoint + rSize )
		{ if ( vNormalize ) NormalizeRect( ); }

	//! CWTRect ���캯��, ͨ��2�� CWTPoint ���� CWTRect ����, 
	/*! \param rTopLeft const CWTPoint ������ ���Ͻ�����
		\param rBottomRight const CWTPoint ������ ���½�����
		\param vNormalize bool �� �ǲ���Ҫ�������� CWTRect ���� 
		\sa CWTRect */
	CWTRect( const CWTPoint& rTopLeft, const CWTPoint& rBottomRight, bool vNormalize = true ) : mTopLeft( rTopLeft ), mBottomRight( rBottomRight )
		{ if ( vNormalize ) NormalizeRect( ); }
public:
	//! CWTRect ���캯��
	~CWTRect( ) {	}

public:
	//! ��Ա���� BottomLeft, 
	/*! \return ����һ��CWTPoint �Ŀ��� */
	CWTPoint BottomLeft( ) const
		{ return CWTPoint( mTopLeft.mX, mBottomRight.mY );	}

	//! ��Ա���� TopRight, 
	/*! \return ����һ��CWTPoint �Ŀ��� */
	CWTPoint TopRight( ) const
		{ return CWTPoint( mBottomRight.mX, mTopLeft.mY );	}

	//! ��Ա���� BottomRight, 
	/*! \return ����һ��CWTPoint �Ŀ��� */
	//CWTPoint BottomRight( ) const
	//	{ return mBottomRight; }

	const CWTPoint& BottomRight() const
		{ return mBottomRight; }

	CWTPoint& BottomRight()
		{ return mBottomRight; }

	//! ��Ա���� TopLeft, 
	/*! \return ����һ��CWTPoint �Ŀ��� */
	//CWTPoint TopLeft( ) const
	//	{ return mTopLeft; }

	const CWTPoint& TopLeft() const
		{ return mTopLeft; }

	CWTPoint& TopLeft()
		{ return mTopLeft; }

	//! ��Ա���� CenterPoint, 
	/*! \return ���ظ� CWTRect ��������ĵ�, һ��CWTPoint �Ŀ��� */
	CWTPoint CenterPoint( ) const
		{ return CWTPoint( ( mTopLeft.mX + mBottomRight.mX ) >> 1, ( mTopLeft.mY + mBottomRight.mY ) >> 1 ); }

	//! ��Ա���� EqualRect, �ж����������Ƿ����
	/*! \param rRect const CWTRect ������
		\return ���ظ� CWTRect �����rRect�Ƿ����, �����ȷ���true, ���򷵻�false */
	bool EqualRect( const CWTRect& rRect )	const
		{ return mTopLeft == rRect.mTopLeft && mBottomRight == rRect.mBottomRight; }

	//! ��Ա���� DeflateRect, ��С�� CWTRect ����, ��Сָ���������Ŀ���
	/*! \param vX int �� mTopLeft�ĺ��������Ӻ�mBottomRight�ĺ����������
		\param vY int �� mTopLeft�����������Ӻ�mBottomRight�������������
		\return û�з���ֵ */
	void DeflateRect( int vX, int vY )
		{ mTopLeft.mX += vX; mTopLeft.mY += vY; mBottomRight.mX -= vX; mBottomRight.mY -= vY; }

	//! ��Ա���� DeflateRect, ��С�� CWTRect ����, ��Сָ���������Ŀ���
	/*! \param rSize const CWTSize �� rSize��mCXָ���� mTopLeft�ĺ��������Ӻ�mBottomRight�ĺ����������
									   rSize��mCYָ���� mTopLeft�����������Ӻ�mBottomRight�������������
		\return û�з���ֵ */
	void DeflateRect( const CWTSize& rSize )
	{ 
		mTopLeft.mX		+= rSize.mCX; mTopLeft.mY		+= rSize.mCY; 
		mBottomRight.mX	-= rSize.mCX; mBottomRight.mY	-= rSize.mCY; 
	}

	//! ��Ա���� DeflateRect, ��С�� CWTRect ����, ��Сָ���������Ŀ���
	/*! \param rRect const CWTRect �� rRect ָ����ÿһ���ߵ���С��
		\return û�з���ֵ */
	void DeflateRect( const CWTRect& rRect )
	{
		mTopLeft.mX		+= rRect.mTopLeft.mX;		mTopLeft.mY		+= rRect.mTopLeft.mY;		
		mBottomRight.mX -= rRect.mBottomRight.mX;	mBottomRight.mY -= rRect.mBottomRight.mY; 
	}

	//! ��Ա���� DeflateRect, ��С�� CWTRect ����, ��Сָ���������Ŀ���
	/*! \param vLeft int �� vLeft ָ���� ��� ��С��
		\param vTop int �� vTop ָ���� �ϱ� ��С��
		\param vRight int �� vRight ָ���� �ұ� ��С��
		\param vBottom int �� vBottom ָ���� �±� ��С��
		\return û�з���ֵ */
	void DeflateRect( int vLeft, int vTop, int vRight, int vBottom )
		{ mTopLeft.mX += vLeft; mTopLeft.mY += vTop; mBottomRight.mX -= vRight; mBottomRight.mY -= vBottom; }

	//! ��Ա���� InflateRect, ����� CWTRect ����, ����ָ���������ķ�ɢ
	/*! \param vX int �� mTopLeft�ĺ�������ٺ�mBottomRight�ĺ�����������
		\param vY int �� mTopLeft����������ٺ�mBottomRight��������������
		\return û�з���ֵ */
	void InflateRect( int vX, int vY )
		{ mTopLeft.mX -= vX; mTopLeft.mY -= vY; mBottomRight.mX += vX; mBottomRight.mY += vY; }

	//! ��Ա���� InflateRect, ����� CWTRect ����, ����ָ���������ķ�ɢ
	/*! \param rSize const CWTSize �� rSize��mCXָ���� mTopLeft�ĺ�������ٺ�mBottomRight�ĺ�����������
									   rSize��mCYָ���� mTopLeft����������ٺ�mBottomRight��������������
		\return û�з���ֵ */
	void InflateRect( const CWTSize& rSize )
	{ 
		mTopLeft.mX		-= rSize.mCX;	mTopLeft.mY		-= rSize.mCY;			
		mBottomRight.mX += rSize.mCX;	mBottomRight.mY	+= rSize.mCY; 
	}

	//! ��Ա���� InflateRect, ����� CWTRect ����, ����ָ���������ķ�ɢ
	/*! \param rRect const CWTRect �� rRect ָ����ÿһ���ߵ�������
		\return û�з���ֵ */
	void InflateRect( const CWTRect& rRect )
	{
		mTopLeft.mX		-= rRect.mTopLeft.mX;		mTopLeft.mY		-= rRect.mTopLeft.mY;	
		mBottomRight.mX += rRect.mBottomRight.mX;	mBottomRight.mY += rRect.mBottomRight.mY; 
	}

	//! ��Ա���� InflateRect, ����� CWTRect ����, ����ָ���������ķ�ɢ
	/*! \param vLeft int �� vLeft ָ���� ��� ������
		\param vTop int �� vTop ָ���� �ϱ� ������
		\param vRight int �� vRight ָ���� �ұ� ������
		\param vBottom int �� vBottom ָ���� �±� ������
		\return û�з���ֵ */
	void InflateRect( int vLeft, int vTop, int vRight, int vBottom )
		{ mTopLeft.mX -= vLeft; mTopLeft.mY -= vTop; mBottomRight.mX += vRight; mBottomRight.mY += vBottom; }

	//! ��Ա���� Height, ���ظ� CWTRect ����ĸ߶�
	/*! \return ���ظ� CWTRect ����ĸ߶� */
	int Height( ) const
		{ return mBottomRight.mY - mTopLeft.mY + 1; }

	//! ��Ա���� Width, ���ظ� CWTRect ����Ŀ��
	/*! \return ���ظ� CWTRect ����Ŀ�� */
	int	Width( ) const	
		{ return mBottomRight.mX - mTopLeft.mX + 1; }

	//! ��Ա���� IsRectEmpty, ���ظ� CWTRect ����Ŀ�͸��ǲ���ȫ����0
	/*! \return ���ظ� CWTRect �����Ƿ����� */
	bool IsRectEmpty( ) const
		{ return Width( ) <= 0 || Height( ) <= 0; }

	//! ��Ա���� IsRectNull, ���ظ� CWTRect ������ĸ����Ƿ�ȫΪ0
	/*! \return ���ظ� CWTRect �����Ƿ�Ϊ0 */
	bool IsRectNull( ) const
		{ return mTopLeft.mX == 0 && mTopLeft.mY == 0 && mBottomRight.mX == 0 && mBottomRight.mY == 0; }

	//! ��Ա���� MoveToX, ����� CWTRect ����vX,�����겻��
	/*! \param vX int �� ָ������ĺ�����
		\return û�з���ֵ */
	void MoveToX( int vX )	
		{ mBottomRight.mX = vX + Width( ); mTopLeft.mX = vX; }

	//! ��Ա���� MoveToY, ����� CWTRect ����vY,�����겻��
	/*! \param vY int �� ָ�������������
		\return û�з���ֵ */
	void MoveToY( int vY )	
		{ mBottomRight.mY = vY + Height( ); mTopLeft.mY = vY; }

	//! ��Ա���� MoveToXY, ����� CWTRect ����vX, vY
	/*! \param vX int �� ָ������ĺ�����
		\param vY int �� ָ�������������
		\return û�з���ֵ */
	void MoveToXY( int vX, int vY )
	{
		mBottomRight.mX = vX + Width( );	mTopLeft.mX	= vX; 
		mBottomRight.mY = vY + Height( ); 	mTopLeft.mY	= vY;  
	}

	//! ��Ա���� MoveToXY, ����� CWTRect ����rPoint
	/*! \param rPoint const CWTPoint ������ ָ�����������
		\return û�з���ֵ */
	void MoveToXY( const CWTPoint& rPoint )
	{
		mBottomRight.mX = rPoint.mX + Width( ); 	mTopLeft.mX = rPoint.mX; 
		mBottomRight.mY = rPoint.mY + Height( );	mTopLeft.mY = rPoint.mY; 
	}

	//! ��Ա���� OffsetRect, �ƶ��� CWTRect ����
	/*! \param vX int �� ָ���������ƫ����
		\param vY int �� ָ���������ƫ����
		\return û�з���ֵ */
	void OffsetRect( int vX, int vY )					 
		{ *this += CWTPoint( vX, vY ); }

	//! ��Ա���� OffsetRect, �ƶ��� CWTRect ����
	/*! \param rPoint const CWTPoint ������ ָ������ƫ����
		\return û�з���ֵ */
	void OffsetRect( const CWTPoint& rPoint )
		{ *this += rPoint; }

	//! ��Ա���� OffsetRect, �ƶ��� CWTRect ����
	/*! \param rSize const CWTSize ������ ָ������ƫ����
		\return û�з���ֵ */
	void OffsetRect( const CWTSize& rSize )				 
		{ *this += rSize; }	

	//! ��Ա���� SetRect, ���� CWTRect ����
	/*! \param vLeft int �� CWTRect��������ϽǺ�����
		\param vTop int �� CWTRect��������Ͻ�������
		\param vRight int �� CWTRect��������½Ǻ�����
		\param vBottom int �� CWTRect��������½�������
		\return û�з���ֵ */
	void SetRect( int vLeft, int vTop, int vRight, int vBottom )
	{
		mTopLeft.mX		= vLeft;	mTopLeft.mY		= vTop; 
		mBottomRight.mX = vRight;	mBottomRight.mY = vBottom; 
	}

	//! ��Ա���� SetRect, ͨ��1�� CWTPoint ��1�� CWTSize ���� CWTRect ����, 
	/*! \param rPoint const CWTPoint ������ ���Ͻ�����
		\param rSize const CWTSize ������ CWTRect�ߴ�	
		\return û�з���ֵ */
	void SetRect( const CWTPoint& rPoint, const CWTSize& rSize )
		{ mTopLeft = rPoint; mBottomRight = rPoint + rSize; }

	//! ��Ա���� SetRect, ͨ��2�� CWTPoint ���� CWTRect ����, 
	/*! \param rTopLeft const CWTPoint ������ ���Ͻ�����
		\param rBottomRight const CWTPoint ������ ���½�����
		\return û�з���ֵ */
	void SetRect( const CWTPoint& rTopLeft, const CWTPoint& rBottomRight )
		{ mTopLeft = rTopLeft; mBottomRight	= rBottomRight; }

	//! ��Ա���� SetRectEmpty, ���� CWTRect ������0, 
	/*! \return û�з���ֵ */
	void SetRectEmpty( )
		{ mTopLeft.mX = 0; mTopLeft.mY = 0; mBottomRight.mX = 0; mBottomRight.mY = 0; }

	//! ��Ա���� Size, ���ظ� CWTRect ����Ŀ�Ⱥ͸߶�
	/*! \return ���ظ� CWTRect ����Ŀ�Ⱥ͸߶� */
	CWTSize Size( ) const
		{ return CWTSize( Width( ), Height( ) ); }

	//! ��Ա���� NormalizeRect, �������� CWTRect ����
	/*! \return û�з���ֵ */
	void NormalizeRect( );

	//! ��Ա���� PtInRect, �ж�ָ�������Ƿ��ڸ� CWTRect ������
    /*! \param rPoint const CWTPoint������ ���жϵ�����
		\return ����ָ�������ǲ����ڸ� CWTRect ������ */
	bool PtInRect( const CWTPoint&	rPoint ) const;

	//! ��Ա���� IntersectRect, �������� CWTRect ����Ľ���
	/*! \brief �����������ľ��β�����, ��ô�þ��ν�������
		\brief eg. CWTRect( ).( CWTRect( 0, 0, 10, 10 ), CWTRect( 5, 5, 15, 15 ) ) == CWTRect( 5, 5, 10, 10 )
		\param const CWTRect& rSrcRect1 Դ����
		\param const CWTRect& rSrcRect2 Դ����
		\return ������������Դ���λ��Ǽ��������ľ��β�������������false, ���ⷵ��true */
   	bool IntersectRect( const CWTRect& rSrcRect1, const CWTRect& rSrcRect2 );

	//! ��Ա���� UnionRect, �������� CWTRect ����Ĳ���
	/*! \brief ������������Դ������һ��������, ����������false
		\brief eg. CWTRect( ).( CWTRect( 0, 0, 10, 10 ), CWTRect( 5, 5, 15, 15 ) ) == CWTRect( 0, 0, 15, 15 )
		\param const CWTRect& rSrcRect1 Դ����
		\param const CWTRect& rSrcRect2 Դ����
		\return ������������Դ������һ��������, ����������false, ���ⷵ��true */
	bool UnionRect( const CWTRect& rSrcRectl, const CWTRect& rSrcRect2 );

	//! �������
	int SubtractRect( const CWTRect& rDesRect, CWTRect* pRectList );

public:
	//! != ������, �ж����� CWTRect �����Ƿ����
	/*! \param const CWTRect& rRect 
		\return ���ظ� CWTRect �����rRect�Ƿ����, �������ȷ���true, ���򷵻�false */
	bool operator != ( const CWTRect& rRect ) const
		{ return !EqualRect( rRect ); }

	//! == ������, �ж����� CWTRect �����Ƿ����
	/*! \param const CWTRect& rRect 
		\return ���ظ� CWTRect �����rRect�Ƿ����, �����ȷ���true, ���򷵻�false */
	bool operator == ( const CWTRect& rRect ) const
		{ return EqualRect( rRect ); }

	//! &= ������, ����� CWTRect ����� ָ�� CWTRect ����Ľ���
	/*! \param const CWTRect& rRect 
		\return û�з���ֵ */
	void operator &= ( const CWTRect& rRect )
		{ IntersectRect( *this, rRect ); }

	//! |= ������, ����� CWTRect ����� ָ�� CWTRect ����Ĳ���
	/*! \param const CWTRect& rRect 
		\return û�з���ֵ */
	void operator |= ( const CWTRect& rRect )
		{ UnionRect( *this, rRect ); }

	//! & ������, ����� CWTRect ����� ָ�� CWTRect ����Ľ���
	/*! \param const CWTRect& rRect 
		\return ����� CWTRect ����� ָ�� CWTRect ����Ĳ���, ���� CWTRect �Ŀ���  */
	CWTRect operator & ( const CWTRect& rRect ) const
	{
		CWTRect tRectResult;
		tRectResult.IntersectRect( *this, rRect );
		return tRectResult;
	}

	//! | ������, ����� CWTRect ����� ָ�� CWTRect ����Ĳ���
	/*! \param const CWTRect& rRect 
		\return ����� CWTRect ����� ָ�� CWTRect ����Ĳ���, ���� CWTRect �Ŀ���  */
	CWTRect operator | ( const CWTRect& rRect ) const
	{
		CWTRect tRectResult;
		tRectResult.UnionRect( *this, rRect );
		return tRectResult;
	}

	//! - ������, �Ѹ� CWTRect ����ƫ�� rPoint ����λ
	/*! \param const CWTPoint& rPoint
		\return �Ѹ� CWTRect ����ƫ�� rPoint ����λ, ���� CWTRect �Ŀ���  */
	CWTRect operator - ( const CWTPoint& rPoint ) const
	{
		CWTRect tRectResult = *this;
		tRectResult.OffsetRect( -rPoint );
		return tRectResult;
	}

	//! - ������, �Ѹ� CWTRect ����ƫ�� rSize ����λ
	/*! \param const CWTSize& rSize
		\return �Ѹ� CWTRect ����ƫ�� rSize ����λ, ���� CWTRect �Ŀ���  */
	CWTRect operator - ( const CWTSize& rSize ) const
	{
		CWTRect tRectResult = *this;
		tRectResult.OffsetRect( -rSize );
		return tRectResult;
	}

	//! - ������, ��С�� CWTRect ������С�ĳߴ��� rRect ָ��
	/*! \param const CWTRect& rRect
		\return ��С�� CWTRect ������С�ĳߴ��� rRect ָ��, ���� CWTRect �Ŀ���  */
	CWTRect operator - ( const CWTRect& rRect ) const
	{
		CWTRect tRectResult = *this;
		tRectResult.DeflateRect( rRect );
		return tRectResult;
	}

	//! + ������, �Ѹ� CWTRect ����ƫ�� rPoint ����λ
	/*! \param const CWTPoint& rPoint
		\return �Ѹ� CWTRect ����ƫ�� rPoint ����λ, ���� CWTRect �Ŀ���  */
	CWTRect operator + ( const CWTPoint& rPoint ) const
	{
		CWTRect tRectResult = *this;
		tRectResult.OffsetRect( rPoint );
		return tRectResult;
	}

	//! + ������, �Ѹ� CWTRect ����ƫ�� rSize ����λ
	/*! \param const CWTSize& rSize
		\return �Ѹ� CWTRect ����ƫ�� rSize ����λ, ���� CWTRect �Ŀ���  */
	CWTRect operator + ( const CWTSize& rSize ) const
	{
		CWTRect tRectResult = *this;
		tRectResult.OffsetRect( rSize );
		return tRectResult;
	}

	//! + ������, ����� CWTRect ��������ĳߴ��� rRect ָ��
	/*! \param const CWTRect& rRect
		\return ����� CWTRect ��������ĳߴ��� rRect ָ��, ���� CWTRect �Ŀ���  */
	CWTRect operator + ( const CWTRect& rRect ) const
	{
		CWTRect tRectResult = *this;
		tRectResult.InflateRect( rRect );
		return tRectResult;
	}

	//! += ������, �Ѹ� CWTRect ����ƫ�� rPoint ����λ
	/*! \param const CWTPoint& rPoint
		\return û�з���ֵ  */
	void operator += ( const CWTPoint& rPoint )
		{ mTopLeft += rPoint; mBottomRight += rPoint; }

	//! += ������, �Ѹ� CWTRect ����ƫ�� rSize ����λ
	/*! \param const CWTSize& rSize
		\return û�з���ֵ  */
	void operator += ( const CWTSize& rSize )
		{ mTopLeft += rSize; mBottomRight += rSize; }

	//! += ������, ����� CWTRect ��������ĳߴ��� rRect ָ��
	/*! \param const CWTRect& rRect
		\return û�з���ֵ  */
	void operator += ( const CWTRect& rRect )
		{ InflateRect( rRect );	}

	//! += ������, �Ѹ� CWTRect ����ƫ�� rPoint ����λ
	/*! \param const CWTPoint& rPoint
		\return û�з���ֵ  */
	void operator -= ( const CWTPoint& rPoint )
		{ mTopLeft -= rPoint; mBottomRight -= rPoint; }

	//! += ������, �Ѹ� CWTRect ����ƫ�� rSize ����λ
	/*! \param const CWTSize& rSize
		\return û�з���ֵ  */
	void operator -= ( const CWTSize& rSize )
		{ mTopLeft -= rSize; mBottomRight -= rSize;	}

	//! += ������, ��С�� CWTRect ������С�ĳߴ��� rRect ָ��
	/*! \param const CWTRect& rRect
		\return û�з���ֵ  */
	void operator -= ( const CWTRect& rRect )
		{ DeflateRect( rRect );	}
};

// ********************************************************************** //
// CSingleton
// ********************************************************************** //

class CTlv
{
public:
	enum
	{
		TLV_TAGLEN			= 16,
		ERROR_OK			= 0,
		ERROR_TAGNOTFOUND	= 1,
		ERROR_TAGOVERRUN	= 2,
	};

	char*	mpBuffer;
	int		mBufferSize;
	int		mPushPointer;

public:
	CTlv( char* pBuffer, int vSize ) : mpBuffer( pBuffer ), mBufferSize( vSize ), mPushPointer( 0 )
	{
	}

	CTlv()
	{
		if ( CObj::msCreateMode )
		{
			mpBuffer = NULL;
			mBufferSize = 0;
			mPushPointer = 0;
		} 
		else
		{
			;
		}
	}

	~CTlv() {}

public:
	int PopBuffer( const char* pTagName, char*& pBuffer, int& rSize );
	int PushBuffer( const char* pTagName, const char* pBuffer, int tSize );
};

// ********************************************************************** //
// CSingleton
// ********************************************************************** //

template< typename T >
class CSingleton
{
private:
	static T* spSingleton;

public:
	CSingleton( )
	{
		spSingleton = static_cast< T* >( this );
	}

	static T* GetSingletonPtr( )
	{
		return spSingleton;
	}

	static T& GetSingleton( )
	{
		return *spSingleton;
	}
};


// ********************************************************************** //
// CLogManager
// ********************************************************************** //

class CLogManager : public CSingleton< CLogManager >
{
public:
	//FILE*	mpSystemLog;		// ϵͳ��־
	//FILE*	mpLogicLog;			// �߼���־

public:
	CLogManager( )
	{
		//mpSystemLog	= ::fopen( "logs/systemlog.txt", "wt" );
		//mpLogicLog	= ::fopen( "logs/logiclog.txt", "wt" );
	}

public:
	~CLogManager( )
	{
		//if ( mpSystemLog != NULL )
		//	::fclose( mpSystemLog );

		//if ( mpLogicLog != NULL )
		//	::fclose( mpLogicLog );
	}

public:
	//void SystemLog( char* pFormat, ... );
	//void LogicLog( char* pFormat, ... );
};

// ********************************************************************** //
// CVariant( ���� )
// ********************************************************************** //

class CVariant
{
public:
	enum VARTYPE
	{
		VT_CHAR		= 0x01,		// char		����
		VT_SHORT	= 0x02,		// short	����
		VT_LONG		= 0x03,		// long		����
		VT_BOOL		= 0x05,		// bool		����
		VT_FLOAT	= 0x06,		// float	����
		VT_DOUBLE	= 0x07,		// double	����
		VT_UCHAR	= 0x11,		// char		����
		VT_USHORT	= 0x12,		// short	����
		VT_ULONG	= 0x13,		// long		����
		VT_PCHAR	= 0x20,		// char*	����
		VT_PSHORT	= 0x21,		// short*	����
		VT_PLONG	= 0x22,		// long*	����
		VT_PFLOAT	= 0x23,		// float*	����
		VT_PDOUBLE	= 0x24,		// double*	����
		VT_PVOID	= 0x25,		// void*	����	
	};

public:
	unsigned short mVarType;			// ��������
	union 
	{
		 char			mCharValue;		// char		����
		 unsigned char	mUCharValue;	// char		����
		 short			mShortValue;	// short	����
		 unsigned short	mUShortValue;	// Ushort	����
		 long			mLongValue;		// long		����
		 unsigned long	mULongValue;	// ULong	����
		 bool			mBoolValue;		// bool		����
		 float			mFloatValue;	// float	����
		 double			mDoubleValue;	// double	����
		 unsigned char* mpCharValue;	// char*	����
		 short*			mpShortValue;	// short*	����
		 long*			mpLongValue;	// long*	����
		 float*			mpFloatVauel;	// float*	���� 
		 double*		mpDoubleValue;  // double*	���� 
		 void*			mpVoidValue;	// void*	���� 
	 };

public:
	CVariant( )
	{
		mVarType	= 0;
		mLongValue	= 0;
	}

public:
	CVariant( unsigned short vVarType, long vVarValue )
	{
		mVarType	= vVarType;
		mLongValue	= vVarValue;
	}
};

// ********************************************************************** //
// CWTimer
// ********************************************************************** //

class CWTimer
{
public:
	int mDuration;
	int mMaxDuration;
public:
	CWTimer()
	{
		if ( CObj::msCreateMode )
		{
			mDuration = 0;
			mMaxDuration = 0;
		} 
		else
		{
			;
		}
	}
	CWTimer( int vDuration ) : mDuration( vDuration ), mMaxDuration( vDuration )	{	}

public:
	// ���ʱ�䵽����true
	inline bool Elapse( int vInterval )
		{ mDuration -= vInterval; return mDuration <= 0 ? mDuration = mMaxDuration, true : false; }
};




enum EGMGateCmdType
{
	CMD_NONE			= 0,
	CMD_FAMILY_MONEY	= 1,	// �����Ǯ
	CMD_FAMILY_BIDNPC	= 2,	// ����NPC
	CMD_FAMILY_BIDMONEY = 3,	// ���۽�Ǯ
	CMD_FAMILY_REPEDATE = 4,	// ��������
	CMD_FAMILY_REPETIME	= 5,	// ��������
	CMD_CORPS_BIDNPC	= 6,	// ����NPC
	CMD_CORPS_BIDMONEY	= 7,	// ���ž���
	CMD_CORPS_BATTLECITY = 8,	// ��������
	CMD_CORPS_ADDCITY	 = 9,	// ���żӳ�
	CMD_CORPS_DELCITY	 = 10,	// ���ż���
	CMD_CORPS_MONEY		 = 11,	// ���Ž�Ǯ
	CMD_WORLD_POWER		 = 12,	// ��������
	CMD_WORLD_WIZARD	 = 13,  // �Ż�ֵ
	CMD_WORLD_CONVALUE	 = 14,	// ����ֵ
	CMD_WORLD_CONWIZARD	 = 15,	// �Ż�����ֵ
	CMD_WORLD_CORPSID	 = 16,	// ����ID
	CMD_WORLD_CLEAR		 = 17,	// ������ܴ���
	CMD_WORLD_PEOPLE	 = 18,	// �����˿�
	CMD_FAMILY_CHASTATUS = 19,	// �������ս��ս��״̬
	CMD_CORPS_CHASTATUS	 = 20,	// ������ս��״̬
	CMD_FAMILY_WARSTATUS = 21,	// ����������״̬	 
	CMD_CORPS_NPC_STATUS = 22,	// ����սNPC��״̬
	CMD_WORLD_CALC_WEAK_LEVEL = 23, // ��ʼ���������ȼ�
};

#define HOUR_TO_SECOND( hour )	( ( hour ) * 60 * 60 )
#define MINUTE_TO_SECOND( min ) ( ( min ) * 60 )
#define DAY_SECOND( hour, min, sec ) ( HOUR_TO_SECOND( hour ) + MINUTE_TO_SECOND( min ) + sec )
#define UN_CONFINE_DATE		( 0 )

struct OpenDate
{
	int mYear;			//��
	int mMonth;			//��
	int mWeek;			//��
	int mDay;			//��( û�ܵĵڼ��� )
	int mHr;			//Сʱ
	int mMinute;		//����
	int mSec;			//��

	OpenDate( ) //: mYear( UN_CONFINE_DATE ), mMonth( UN_CONFINE_DATE ), mWeek( UN_CONFINE_DATE ),
//		mDay( UN_CONFINE_DATE ), mHr( UN_CONFINE_DATE ), mMinute( UN_CONFINE_DATE ), mSec( UN_CONFINE_DATE )
	{ 
		if( CObj::msCreateMode )
		{
			Clear( );
		}
	}

	void Clear( )
	{
		mYear = UN_CONFINE_DATE;
		mMonth = UN_CONFINE_DATE;
		mWeek = UN_CONFINE_DATE;
		mDay = UN_CONFINE_DATE;
		mHr = UN_CONFINE_DATE;
		mMinute = UN_CONFINE_DATE;
		mSec = UN_CONFINE_DATE;

	}
};

struct DateSpace
{
	OpenDate mBegin;
	OpenDate mEnd;
	
	void Clear( )
	{
		mBegin.Clear( );
		mEnd.Clear( );
	}

	bool InDateSpace( struct tm* vTm )
	{
		if( mBegin.mYear != UN_CONFINE_DATE )
		{
			if( ( vTm->tm_year + 1900 ) >= mBegin.mYear )
			{
				if( mEnd.mYear != UN_CONFINE_DATE )
				{
					if( ( vTm->tm_year + 1900 ) > mEnd.mYear )
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}
		}

		if( mBegin.mMonth != UN_CONFINE_DATE )
		{
			if( vTm->tm_mon < mBegin.mMonth )
			{
				return false;
			}

			if( mEnd.mMonth != UN_CONFINE_DATE )
			{
				if( vTm->tm_mon > mEnd.mMonth )
				{
					return false;
				}
			}
		}

		if( mBegin.mWeek != UN_CONFINE_DATE )
		{
			int tWeek = vTm->tm_wday;//( abs( vTm->tm_mday - vTm->tm_wday + 1 ) / 7 ) + 1;
			tWeek = ( vTm->tm_wday != 0 ) ? vTm->tm_wday : 7;
			if( tWeek < mBegin.mWeek )
			{
				return false;
			}

			if( mEnd.mWeek != UN_CONFINE_DATE )
			{
				if( tWeek > mEnd.mWeek )
				{
					return false;
				}
			}
		}

		if( mBegin.mDay != UN_CONFINE_DATE )
		{
			if( vTm->tm_mday < mBegin.mDay )
			{
				return false;
			}

			if( mEnd.mDay != UN_CONFINE_DATE )
			{
				if( vTm->tm_mday > mEnd.mDay )
				{
					return false;
				}
			}
		}

		if( mBegin.mHr != UN_CONFINE_DATE || mEnd.mHr != UN_CONFINE_DATE )
		{
			if( mEnd.mHr != UN_CONFINE_DATE )
			{
				unsigned int tDayTimeNow = DAY_SECOND( vTm->tm_hour, vTm->tm_min, vTm->tm_sec );
				unsigned int tDayTimeBegin = DAY_SECOND( mBegin.mHr, mBegin.mMinute, mBegin.mSec );
				unsigned int tDayTimeEnd = DAY_SECOND( mEnd.mHr, mEnd.mMinute, mEnd.mSec );

				if( ( tDayTimeNow >= tDayTimeBegin ) && ( tDayTimeNow < tDayTimeEnd ) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if( vTm->tm_hour >= mBegin.mHr )
				{
					return true;
				}
			}
		}

		return true;
	}
};



//
//// ********************************************************************** //
//// CDispParams���ӿڲ�����Ϣ(����������)
//// ********************************************************************** //
//
//class CDispParams
//{
//public:
//	unsigned int	mNumberOfArgs;		// �м�������
//	CVariant		mVariants[ 16 ];		// ������, ���8������
//
//public:
//	CDispParams( ) : mNumberOfArgs( 0 )
//	{
//	}
//
//public:
//	void PushParam( const CVariant& rVar )
//	{
//		mVariants[ mNumberOfArgs ] = rVar;
//		mNumberOfArgs ++ ;
//	}
//};
//
//// ********************************************************************** //
//// CCommandHandler
//// ********************************************************************** //
//
//template < typename T >
//class CCommandHandler
//{
//	typedef void ( T::*CommandProc )( std::vector< std::string >& rParam );
//
//public:	
//	std::string		mCommand;
//	CommandProc		mpHandler;
//	T*				mpClass;
//
//public:
//	CCommandHandler( const char* pCommand = "", T* pClass = NULL, CommandProc pHandler = NULL ) : mCommand( pCommand ), mpClass( pClass ), mpHandler( pHandler )
//	{
//	}
//
//public:
//	void Fire( std::vector< std::string >& rParam )
//		{ ( mpClass->*mpHandler )( rParam ); }
//};
//
//// ********************************************************************** //
//// CCommandCenter
//// ********************************************************************** //
//
//template < typename T >
//class CCommandCenter
//{
//protected:
//	std::vector< CCommandHandler< T > >		mCommandList;
//	bool									mRun;
//
//public:
//	CCommandCenter( ) : mRun( true )
//	{
//	}
//
//public:
//	void Exit( )
//	{
//		mRun = false;
//	}
//
//public:
//	// ע�ᴦ����
//	void RegisterCommand( CCommandHandler< T > vHandler )
//		{ mCommandList.push_back( vHandler ); }
//
//	// ִ��
//	//���� �ػ����̴����ж�
//	void Run( const int nDaemon = 0)
//	{
//		std::string tCommandString;
//		std::vector< std::string > tParam;
//		while( mRun == true )
//		{
//			if (nDaemon==0)
//			{
//				int tChar = ::getchar( );
//				if ( tChar == ' ' || tChar == '\n' )
//				{
//					tParam.push_back( tCommandString );
//					tCommandString.clear( );
//				}
//				else
//					tCommandString.push_back( tChar );
//
//				if ( tChar == '\n' )
//				{
//					size_t i = 0;
//					for ( ; i < mCommandList.size( ); i ++ )
//					{
//						if ( strcmp( mCommandList[ i ].mCommand.c_str( ), tParam[ 0 ].c_str( ) ) == 0 )
//						{
//							mCommandList[ i ].Fire( tParam );
//							break;
//						}
//					}
//
//					if ( i == mCommandList.size( ) && tParam[ 0 ].empty( ) == false )
//					{
//						printf( "Invalid Command!\r\n" );
//					}
//					tParam.clear( );
//				}
//			}
//#ifdef LINUX
//			else
//				sleep(1);
//#endif
//
//		}
//	}
//};
//
//#ifdef WIN32
//// ********************************************************************** //
//// CException
//// ********************************************************************** //
//
//struct CException
//{
//	char*	mpFileName;
//	int		mLineNumber;
//	char	mDesc[2048];
//
//	CException( char* pFileName, int vLineNumber ) : mpFileName( pFileName ), mLineNumber( vLineNumber ) { }
//};
//
//// ********************************************************************** //
//// CExceptionManager
//// ********************************************************************** //
//
//class CExceptionManager
//{
//public:
//	static void*	spPreviousFilter;
//	static void*	spProcessHandle;
//	static char		mErrorDesc[ 8192 ];
//public:
//	static void Initialize( );
//	static void Finalize( );
//
//	static long __stdcall ExceptionFilter( void* pExceptionInfo );
//
//	static char* GetExceptionString( int vCode );
//	static bool	 GetLogicalAddress( void* pAddress, char* pBuffer, int vLength, int* pSection, int* pOffset );
//
//	static void DumpStack( void* pContext );
//};


//#endif
#endif


