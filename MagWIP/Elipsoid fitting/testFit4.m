clear all
clc

% generate test data:
[s, t]=meshgrid([0:0.3:pi/2], [0:0.3:pi]);
% create test data:
a=10; b=7; c=5;
xx=a*cos(s).*cos(t);
yy=b*cos(s).*sin(t);
zz=c*sin(s);
% add testing noise:
noiseIntensity = 0.0;
xx=xx+randn(size(s))*noiseIntensity;
yy=yy+randn(size(s))*noiseIntensity;
zz=zz+randn(size(s))*noiseIntensity;
% do the fitting
dx=xx(:); dy=yy(:); dz=zz(:);
n=size(dx,1);
D=[dx.*dx, dy.*dy,  dz.*dz, 2.*dy.*dz, 2.*dx.*dz, 2.*dx.*dy, ...
        2.*dx, 2.*dy, 2.*dz, ones(n,1)]';
S=D*D';
v=FindFit4(S);
minX=min(dx);  maxX=max(dx);
minY=min(dy);  maxY=max(dy);
minZ=min(dz);  maxZ=max(dz);
% draw fitting:
nStep=20;
stepA=a/nStep; stepB=b/nStep; stepC=c/nStep;
[x, y, z]=meshgrid(-a:stepA:a, -b:stepB:b, -c:stepC:c);
SolidObj=v(1)*x.*x+v(2)* y.*y+v(3)*z.*z+ 2*v(4)*y.*z + 2*v(5)*x.*z + 2*v(6)*x.*y...
    + 2*v(7)*x + 2*v(8)*y + 2*v(9)*z + v(10)* ones(size(x));
clf;
       p = patch(isosurface(x,y,z,SolidObj, 0.0));
       isonormals(x,y,z,SolidObj, p);
       set(p, 'FaceColor', 'y', 'EdgeColor', 'none');
       daspect([1 1 1]);
       view(3);
       camlight ;
       lighting phong;
       hold on;
plot3(dx, dy, dz, 'o');

A=[v(1),v(6),v(5);v(6),v(2),v(4);v(5),v(4),v(3);];

p=inv(A)*[(-v(7)),(-v(8)),(-v(9)) ]';

[V,Diag] = eig(A);

V2=flip(V,2);

%grid
gridlim=20;
[~,grid]=meshgrid(1:3,-gridlim:1:gridlim);
Xgrid=(grid*diag(V(:,1)));
Ygrid=(grid*diag(V(:,2)));
Zgrid=(grid*diag(V(:,3)));

Xgrid2=(grid*diag(V2(:,1)));
Ygrid2=(grid*diag(V2(:,2)));
Zgrid2=(grid*diag(V2(:,3)));
%V2(:,1)
hold on;
plot3(Xgrid(:,1),Xgrid(:,2),Xgrid(:,3),'g');
plot3(Ygrid(:,1),Ygrid(:,2),Ygrid(:,3),'g');
plot3(Zgrid(:,1),Zgrid(:,2),Zgrid(:,3),'g');

%plot3(Xgrid2(:,1),Xgrid2(:,2),Xgrid2(:,3),'k');
%plot3(Ygrid2(:,1),Ygrid2(:,2),Ygrid2(:,3),'k');
%plot3(Zgrid2(:,1),Zgrid2(:,2),Zgrid2(:,3),'k');

hold off;



