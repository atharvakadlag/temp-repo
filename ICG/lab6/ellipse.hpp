#include<bits/stdc++.h>

#define ellipse vector<pair<int, int>>
#define point pair<int, int>
using namespace std;

ellipse MP_ELLIPSE(int rx, int ry,
				int xc, int yc)
{
    ellipse e1;
	float dx, dy, p1, p2, x, y;
	x = 0;
	y = ry;

	p1 = (ry * ry) - (rx * rx * ry) +
					(0.25 * rx * rx);
	dx = 2 * ry * ry * x;
	dy = 2 * rx * rx * y;

	while (dx < dy)
	{

		e1.push_back(point(x + xc, y + yc));
		e1.push_back(point(-x + xc, y + yc));
		e1.push_back(point(x + xc, -y + yc));
		e1.push_back(point(-x + xc, -y + yc));

		if (p1 < 0)
		{
			x++;
			dx = dx + (2 * ry * ry);
			p1 = p1 + dx + (ry * ry);
		}
		else
		{
			x++;
			y--;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			p1 = p1 + dx - dy + (ry * ry);
		}
	}

	p2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
		((rx * rx) * ((y - 1) * (y - 1))) -
		(rx * rx * ry * ry);

	while (y >= 0)
	{

		e1.push_back(point(x + xc, y + yc));
		e1.push_back(point(-x + xc, y + yc));
		e1.push_back(point(x + xc, -y + yc));
		e1.push_back(point(-x + xc, -y + yc));

		if (p2 > 0)
		{
			y--;
			dy = dy - (2 * rx * rx);
			p2 = p2 + (rx * rx) - dy;
		}
		else
		{
			y--;
			x++;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			p2 = p2 + dx - dy + (rx * rx);
		}
	}
    return e1;
}

