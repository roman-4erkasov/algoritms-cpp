bool move(int direction,int **ar)
{
  if(direction==0)
    if(ar[i++][j]==0)
      return true;
  if(direction==1)
    if(ar[i][j--]==0)
      return true;
  if(direction==2)
    if(ar[i--][j]==0)
      return true;

  if(direction==3)
    if(ar[i][j++]==0)
      return true;
  return false;

}

int findarea(int area,int **ar,int i,int j)
{
  if(ar[i++][j] == 1 && ar[i][j--]=1 && ar[i--][j]=1 && ar[i][j++]=1)
    return area;
  else
    {
      if(move(0,ar,i,j))
	{
	  area++;
	  ar[i++][j]=1;
	  findarea(area,ar,i,j);
	}
      if(move(1,ar,i,j))
	{
	  area++;
	  ar[i][j--]=1;
	  findarea(area,ar,i,j);
	}
      if(move(2,ar,i,j))
	{
	  area++;
	  ar[i--][j]=1;
	  findarea(area,ar,i,j);
	}
      if(move(3,area,i,j))
	{
	  area++;
	  ar[i][j++]=1;
	  findarea(area,ar,i,j);
	}

    }
  return 1;
}

int main()
{
  int area=1;
  int r=0,c=0;
  int **ar = (int **)malloc(r * sizeof(int *));
  for (r=0; r<;200; r++)
    ar[r] = (int *)malloc(c * sizeof(int));
  for(r=0;r<;200;r++)
    for(c=0;c<;200;c++)
      ar[r][c]=0;
  ar[0][0]=1;
  cout<<findarea(area,ar,0,0);
  return 0;
}
