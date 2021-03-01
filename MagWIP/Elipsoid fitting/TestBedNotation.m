clc;
clear all;
%set(0,'DefaultFigureVisible','on');
%D=[1 2 3 4 ; 5 6 7 8 ; 8 9 10 11];
%A = D';
%S = D * D';

%Thats nasty
%{
k=4;

c(1,:)=[-1,((k/2)-1),((k/2)-1),0,0,0];
c(2,:)=[((k/2)-1),-1,((k/2)-1),0,0,0];
c(3,:)=[((k/2)-1),((k/2)-1),-1,0,0,0];
c(4,:)=[0,0,0,-k,0,0];
c(5,:)=[0,0,0,0,-k,0];
c(6,:)=[0,0,0,0,0,-k];
%}
%{
max_lim = 75000;
v=  [-0.6;
    -0.5;
    -0.5;
    0.0;
    -0.01;
    0.01;
    -5000;
    -9000;
    -1500;
    900000000];

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
%temp=(-v(7) -v(8) -v(9) )';
p=inv(A)*(-v(7) -v(8) -v(9) )';

C=p'*A*p-v(10);
%}


