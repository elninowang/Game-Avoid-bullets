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
			wsprintf(str,"你褂了！你只坚持了%d秒，你太没用了，你不是男人，点击确定重新开始!",RealTime);
			MessageBox(NULL, TEXT(str),TEXT("准备开始"),NULL);
		}
		else if( RealTime <40 )
		{
			wsprintf(str,"你褂了！但你坚持了%d秒，你是男人，一个普通的男人！你还要努力",RealTime);
			MessageBox(NULL, TEXT(str),TEXT("准备开始"),NULL);
		}
		else 
		{
			wsprintf(str,"你褂了！我太佩服你了，你坚持了%d秒，你是一个超级男人，你无敌了！",RealTime );
			MessageBox(NULL, TEXT(str),TEXT("准备开始"),NULL);
		}
		Restart();
		return false;
	}
	return true;
}
