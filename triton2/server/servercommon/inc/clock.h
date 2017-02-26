// ***************************************************************
//  File:	clock.h   version:  1.0
//	Date:	05/23/2008
// 	Desc:	��װʱ�Ӻ���
//  
//  Copyright (C) 2008 - LineKong Entertainment Technology Co.,Ltd
//						All Rights Reserved 
// ***************************************************************
#pragma once



class Clock
{
public:
    Clock();
    ~Clock();

    bool				active() const	{ return _active; }
    int					elapsed() const;
    unsigned int		start();
    unsigned int		reset() { return start(); }
    int					stop();

    static unsigned long long   now();

private:

    unsigned int	_start;		/// ��ʼ��ʱ��
    int				_elapsed;	/// ����ʱ������ʱ��
    bool			_active;	/// �Ƿ��ڻ״̬
};
