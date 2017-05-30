void Restart()
{
	int i;

	RealTime = 0;

	pl.Restart();
	for( i=0;i<BLOCK_NUM;i++ )
		bl[i].Restart();
}
void Draw()
{
	int i;
	pl.Show();
	for( i=0;i<BLOCK_NUM;i++ )
		bl[i].Show();
}
bool Check()
{
	int i;
	for( i=0;i<BLOCK_NUM;i++ )
		if( !bl[i].CheckHit(pl) )
			return false;
	return true;
}