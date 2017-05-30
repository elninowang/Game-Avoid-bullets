Plane::Plane(int xX,int yY)
{
	xN = xX;
	yN = yY;
	vX = 0;
	vY = 0;
}
int Plane::xLeft()
{
	return xN-cxPlane/2;
}
int Plane::xRight()
{
	return xN+cxPlane/2;
}
int Plane::yTop()
{
	return yN-cyPlane/2;
}
int Plane::yBottom()
{
	return yN+cyPlane/2;
}
void Plane::UpVLeft()
{
	if( vX >= -MAXPV )
		vX-=AV;
}
void Plane::UpVRight()
{
	if( vX <= MAXPV )
		vX+=AV;
}
void Plane::UpVUp()
{
	if( vY >= -MAXPV )
		vY-=AV;
}
void Plane::UpVDown()
{
	if( vY <= MAXPV )
		vY+=AV;
}
void Plane::Show()
{
	lpDDBack->BltFast( xLeft(), yTop(), lpDDPlane, NULL ,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
}
void Plane::Next()
{
	if( xLeft()+vX <= 0 )
	{
		xN = cxPlane/2;
		vX = -vX;
		yN+=vY;
		return;
	}
	if( xRight()+vX >= cxSurface )
	{
		xN = cxSurface-cxPlane/2;
		vX = -vX;
		yN+=vY;
		return;

	}
	if( yTop()+vY <= 0 )
	{
		yN = cyPlane/2;
		vY = -vY;
		xN+=vX;
		return;
	}
	if( yBottom()+vY >=cySurface )
	{
		yN = cySurface-cyPlane/2;
		vY = -vY;
		xN+=vX;
		return;
	}
	else
	{
		xN+=vX;
		yN+=vY;
	}
}
void Plane::Restart()
{
	xN = cxSurface/2;
	yN = cySurface/2;
	vX = 0;
	vY = 0;
}


///////////////////////////////////////////////////////////////
Block::Block(int xX,int yY)
{
	xN = xX;
	yN = yY;
}
int Block::xLeft()
{
	return xN-cxBlock/2;
}
int Block::xRight()
{
	return xN+cxBlock/2;
}
int Block::yTop()
{
	return yN-cyBlock/2;
}
int Block::yBottom()
{
	return yN+cyBlock/2;
}
void Block::Show()
{
	lpDDBack->BltFast( xLeft(), yTop(), lpDDBlock, NULL ,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY );
}
void Block::Next()
{
	if( xLeft()+vX <= 0 )
	{
		xN = cxBlock/2;
		vX = -vX;
		return;
	}
	if( xRight()+vX >= cxSurface )
	{
		xN = cxSurface-cxBlock/2;
		vX = -vX;
		return;

	}
	if( yTop()+vY <= 0 )
	{
		yN = cyBlock/2;
		vY = -vY;
		return;
	}
	if( yBottom()+vY >=cySurface )
	{
		yN = cySurface-cyBlock/2;
		vY = -vY;
		return;
	}
	else
	{
		xN+=vX;
		yN+=vY;
	}
}
int Rand(int nA)
{
	return rand()%nA;
}
int Rand(int nMid,int nOff)
{
	int nRand = Rand(nOff)+1;
	int flags = Rand(2);
	if( flags )
		return nMid+nRand;
	else
		return nMid-nRand;
}
Block::Block()
{
	int nRand=Rand(4);
	if( nRand == 0 )
	{
		xN = Rand(cxSurface);
		yN = cyBlock/2;
		vX = Rand(0,MAXV);
		vY = Rand(MAXV)+1;
	}
	else if( nRand == 1 )
	{
		xN = cxBlock/2;
		yN = Rand(cySurface);
		vX = Rand(MAXV)+1;
		vY = Rand(0,MAXV);
	}
	else if( nRand == 2 )
	{
		xN = Rand(cxSurface);
		yN = cySurface-cyBlock/2;
		vX = Rand(0,MAXV);
		vY = -Rand(MAXV)-1;
	}
	else if( nRand == 3 )
	{
		xN = cxSurface-cxBlock/2;
		yN = Rand(cySurface);
		vX = -Rand(MAXV)-1;
		vY = Rand(0,MAXV);
	}
	else 
	{
		xN = cxSurface/2;
		yN = cySurface/2;
		vX = 0;
		vY = 0;
	}
}
void Block::Restart()
{
	int nRand=Rand(4);
	if( nRand == 0 )
	{
		xN = Rand(cxSurface);
		yN = cyBlock/2;
		vX = Rand(0,MAXV);
		vY = Rand(MAXV)+1;
	}
	else if( nRand == 1 )
	{
		xN = cxBlock/2;
		yN = Rand(cySurface);
		vX = Rand(MAXV)+1;
		vY = Rand(0,MAXV);
	}
	else if( nRand == 2 )
	{
		xN = Rand(cxSurface);
		yN = cySurface-cyBlock/2;
		vX = Rand(0,MAXV);
		vY = -Rand(MAXV)-1;
	}
	else if( nRand == 3 )
	{
		xN = cxSurface-cxBlock/2;
		yN = Rand(cySurface);
		vX = -Rand(MAXV)-1;
		vY = Rand(0,MAXV);
	}
	else 
	{
		xN = cxSurface/2;
		yN = cySurface/2;
		vX = 0;
		vY = 0;
	}
}
bool Block::CheckHit(Plane p)
{
	if( xN>=p.xLeft()+2 && xN<=p.xRight()-2  && yN>=p.yTop()+2 && yN<=p.yBottom()-2 )
		return false;
	return true;
}
