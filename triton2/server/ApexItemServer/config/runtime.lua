--���� �� Client��������;
function RegisterClientMem()
		--cltmem_user_var("zhenshi",4);
		--cltmem_user_var("flag",1);
		--timer_var("baobaoency", 180000, 1 );
		
		--cltmem_user_var("nDrvOk",1);
		--timer_var("DrvBoom", 180000, 2 );
		
		cltmem_user_var("check_resinfo",100);
		return 0;
end;
-------------------------------------------------------------------------------------------------------------
-- // ���ݷ���ֵ����
-- // ���������������������
-- // ���Lua����2��ᱻ��
function HandleDrvRet( nRet, nDebugRet )
			if(nRet == 4321 and nDebugRet == 2 ) then
					return 0;
			else
					return 0;
			end		
		return 0;	
end;
-----------------------------------------------------------------------------------------------------------
-- //���ɨ��������״̬
-- //˵����nScanStart 	���Ƿ���������
-- //      nCurInstCt   ����ǰָ�������
-- //			 nCurInstId   ����ǰָ�������
-- //      nTickCN      : �ڵ�ǰָ��ͣ���Ĵ���
-- //����ֵΪ 1 ����
function HandleXVMInst( nScanStart,nCurInstCt, nCurInstId,nTickCN )
			
			if( nTickCN == 20 and nScanStart == 1 )then
					return 0;
			else
					return 0; 
			end
			return 0;
									
end;
------------------------------------------------------------------------------------------------------------
-- //���ͻ����߳����
-- //˵����
-- //nThreadId�����Ǹ��̴߳������⣺1����apex2���̣߳� 2����apex2ɨ���߳�
-- //nErrType�������ԭ��					��1�����߳���ͣ��    2�����߳���ֹ	
-- //����1����2������							
function HandleThreadErr( nThreadId, nErrType )
			--svr_log( string.format("%d,%d",nThreadId, nErrType) );
		
			if( nErrType>0 and nErrType<3)then
					return 1;
			end
			
			return 0;
end;
-----------------------------------------------------------------------------------------------------------
-- //���Apex2��CRC32У��ֵ����������    ����0����������2����¼�����ߣ�����1����61086��61087�ߣ�
function HandleApex2CRC( nID, uCrc32 )
		--if( uCrc32 ==0 )then
		--	logInT = mem_r("m_tLogin");
		--	curT   = gettickcount();
		--	diff 	 = curT - logInT;	
		--	if(diff>180000 and diff<200000)then
		--		svr_log( string.format( "Apex2ClientCRCErr") );
		--		return 1;
		--	end
		--	return 0;
		--end
		--
		--if( string.format("0x%08x",uCrc32) == "0xa25f47bf" )then
		--		return 0;
		--else
		--    return 1;
		--end;
	return 0;	
end;
--------------------------------------------------------------------------------------------------------
--�������Ƿ���� �Լ� ����
function TestServer()
    nflag       =	mem_r("flag");
    if( (nflag == 0) or (nflag == 2))then
		return 0;
    end
    nGetNumber  = mem_r("zhenshi");
    
	nUserCount	=	mem_r("m_nCltCount");
	nGetId		=   mod(nUserCount,212);
	nGetId		=   nGetId + 7;
	nGetId      =   mod(nGetId,13);
	
	nMod		=   mod(nUserCount,53);
	nMod		=   nMod + 17;
	
	if( nGetId == 0)then
		nNumber = 88+11*2-7+2*nMod-6+12+3*4-1*2+1;
	elseif( nGetId == 2)then
		nNumber = 56-12-11-10+nMod-nMod+3+354-16+nMod*2+2;
	elseif( nGetId == 3)then
		nNumber =  12*5+3*nMod-2*3+3+3-2+nMod*4+3+2+1;
	elseif( nGetId == 5)then
		nNumber = 8*8-2*3-1*3*2+nMod+4+32+3*nMod*2+56;
	elseif( nGetId == 7)then
		nNumber = 6*nMod-2*nMod+16-12+3+8+3+8+28+5*1+nMod-3;
	else
		nNumber = nMod+9+nMod*2-2+156-nMod+nMod*6+16+3+9*0+2;
	end
	
	svr_log( string.format("id:%d,CmnTclose:%d,%d",nGetId,nGetNumber,nNumber ) );
	if(nGetNumber == nNumber)then
		timer_close("baobaoency");
	end
	mem_w("flag",2);
end
---------------------------------------------------------------------------------------------------------
function TickDrvRet()
	nflag       = mem_r("nDrvOk");
	nOsId       = mem_r("uOSVer");
	
	if( nflag > 17)then
		if( nOsId >= 0x50)then
			timer_close("DrvBoom");
			svr_log( string.format( "OsV7NoSend") );
			mem_w("nDrvOk",1);
			return 1;
		end
		if(nflag == 18)then
			timer_close("DrvBoom");
			svr_log( string.format( "DrvLoadOk") );
			mem_w("nDrvOk",1);
			return 2;
		end
	end
	return 0;
end

function HelloTick()

	--TestServer();
	--TickDrvRet();
 	return  0;
end
-------------------------------------------------------------------------------------------------------
--�������ͻ����߳������Ϳͻ����Ƿ���KillNO���͵�������
function HandleCltState( nNumOfCltThread, nNumOfKillNotify )
			
			--svr_log(string.format("HandleCltState :%d, %d", nNumOfCltThread,nNumOfKillNotify));
			
			return 0;
end;

function HelloTickUser( m_tOnline, m_tLogin, m_nCmnFlag )
	
	nOsId       = mem_r("uOSVer");
	if( ((nOsId >= 0x60) and (nOsId < 0x80) ) or (nOsId >= 0x90) )then           --64λ��δʵ��
		return 0;
	end
	
	if( m_tOnline > 60*1000 and ( And( m_nCmnFlag, 0x00080000) == 0 ) )then      --�������࿪
		svr_kill(62500);
	end;
	
	if( m_tOnline > 60*1000 and ( And( m_nCmnFlag, 0x00100000) == 0 ) )then       --�������࿪
		svr_kill(62501);
	end;
	
	if( m_tOnline > 60*1000 and ( And( m_nCmnFlag, 0x00200000) == 0 ) )then       --�ϲ���ѻ�
		svr_kill(62502);
	end;
	
	return 0;
end;

function HelloTickGame( nCrc)
	--svr_log( string.format("TickG: %08x",nCrc));
	
	if( string.format("0x%08x",nCrc) == "0xbc9b8b0b" )then
	  return 0;
	end;
	
	svr_kill(62503);
	return 0;
end