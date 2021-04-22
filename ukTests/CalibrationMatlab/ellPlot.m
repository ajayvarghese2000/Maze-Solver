function ellPlot(v,max_lim)
%max_lim = 75000;

a=max_lim;  b=max_lim;  c=max_lim;
nStep=20;
stepA=a/nStep; stepB=b/nStep; stepC=c/nStep;
[x, y, z]=meshgrid(-a:stepA:a, -b:stepB:b, -c:stepC:c);

SolidObj=v(1)*x.*x+v(2)* y.*y+v(3)*z.*z+ 2*v(4)*y.*z + 2*v(5)*x.*z + 2*v(6)*x.*y...
    + 2*v(7)*x + 2*v(8)*y + 2*v(9)*z + v(10)* ones(size(x));

p = patch(isosurface(x,y,z,SolidObj, 0.0));
isonormals(x,y,z,SolidObj, p);
set(p, 'FaceColor', 'r', 'EdgeColor', 'none');
daspect([1 1 1]);
view(3);
camlight ;
xlabel('x-axis')
ylabel('y-axis')
zlabel('z-axis')
lighting phong;

end