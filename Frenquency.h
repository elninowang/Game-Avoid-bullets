int iTime = 0;
int iTempTime = 2;
bool TimeFunction()
{
	int i;
	iTime++;
	if( iTime==iTempTime )
	{
		iTime = 0;
		pl.Next();
		for( i=0;i<BLOCK_NUM;i++ )
		{
			bl[i].Next();
		}
		DrawDirectX( hWnd );
	}
	if( !Check() )
	{
		char str[100];
		if( RealTime < 20 )
		{
			wsprintf(str,"����ˣ���ֻ�����%d�룬��̫û���ˣ��㲻�����ˣ����ȷ�����¿�ʼ!",RealTime);
			MessageBox(NULL, TEXT(str),TEXT("׼����ʼ"),NULL);
		}
		else if( RealTime <40 )
		{
			wsprintf(str,"����ˣ���������%d�룬�������ˣ�һ����ͨ�����ˣ��㻹ҪŬ��",RealTime);
			MessageBox(NULL, TEXT(str),TEXT("׼����ʼ"),NULL);
		}
		else 
		{
			wsprintf(str,"����ˣ���̫������ˣ�������%d�룬����һ���������ˣ����޵��ˣ�",RealTime );
			MessageBox(NULL, TEXT(str),TEXT("׼����ʼ"),NULL);
		}
		Restart();
		return false;
	}
	return true;
}
