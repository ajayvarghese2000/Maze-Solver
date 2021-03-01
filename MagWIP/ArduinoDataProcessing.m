clear all;
clc;

fID = fopen('Test.txt','r');
data = fscanf(fID,'%f\t%f\t%f',[3,inf]);
fclose(fID);
dx=data(1,:)';
dy=data(2,:)';
dz=data(3,:)';
plot3(dx,dy,dz,'ko')

max_lim = 75000;


n=size(dx,1);
D=[dx.*dx, dy.*dy,  dz.*dz, 2.*dy.*dz, 2.*dx.*dz, 2.*dx.*dy, ...
        2.*dx, 2.*dy, 2.*dz, ones(n,1)]';

v=liFit(D*D');
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
lighting phong;

A=[v(1),v(6),v(5);v(6),v(2),v(4);v(5),v(4),v(3);];
%pcomp=[(-v(7)),(-v(8)),(-v(9)) ]';
p=inv(A)*[(-v(7)),(-v(8)),(-v(9)) ]';

C=p'*A*p-v(10);


[V,Diag] = eig(A);
cons=2;
temp=A-[Diag(cons,cons) ,0 ,0;0 ,Diag(cons,cons) ,0; 0 ,0 ,Diag(cons,cons)];

temp2=temp*V(:,cons);



