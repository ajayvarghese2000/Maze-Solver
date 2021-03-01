clear all
clc
%fix scaling
max_lim = 75000;

% generate test data:
[s, t]=meshgrid([0:0.3:pi/2], [0:0.3:pi]);
% create test data:
a=70000; b=40000; c=30000;
xx=a*cos(s).*cos(t);
yy=b*cos(s).*sin(t);
zz=c*sin(s);
% add testing noise:
noiseIntensity =(a/50) * 0.5;
xx=xx+randn(size(s))*noiseIntensity;
yy=yy+randn(size(s))*noiseIntensity;
zz=zz+randn(size(s))*noiseIntensity;
% do the fitting
dx=xx(:); dy=yy(:); dz=zz(:);

data= [dx' ; dy' ; dz'];

v=proc(data);

A=[v(1),v(6),v(5);v(6),v(2),v(4);v(5),v(4),v(3);];

p=inv(A)*[(-v(7)),(-v(8)),(-v(9)) ]';
[V,Diag] = eig(A);

figure(2);

data = data - p;
hold on
ellPlot(v,max_lim);
plot3(data(1,:),data(2,:),data(3,:),'ko')
hold off
figure(3)

 
data2 = inv(flip(V,2)) * data;
%data2 = data4*data2;


v2=ProcAndPlot(data2);
A2=[v2(1),v2(6),v2(5);v2(6),v2(2),v2(4);v2(5),v2(4),v2(3);];
v3=v2./v2(10);% divide
[V2,Diag2] = eig(A2);

%data3(1,:) = data2(1,:)./v2(1);
%data3(2,:) = data2(2,:)./v2(2);
%data3(3,:) = data2(3,:)./v2(3);
figure(4)
%v3=ProcAndPlot(data3);
newa=sqrt(1/abs(v3(1)));
newb=sqrt(1/abs(v3(2)));
newc=sqrt(1/abs(v3(3)));


data3(1,:) = (data2(1,:)./newa)*50000;
data3(2,:) = (data2(2,:)./newb)*50000;
data3(3,:) = (data2(3,:)./newc)*50000;

v4=ProcAndPlot(data3);

figure(5)

data5 = flip(flip(Diag,2),1);

newa1=sqrt(1/abs(Diag2(3,3)./v2(10)));
newb1=sqrt(1/abs(Diag2(2,2)./v2(10)));
newc1=sqrt(1/abs(Diag2(1,1)./v2(10)));

data4(1,:) = (data2(1,:)./newa1)*50000;
data4(2,:) = (data2(2,:)./newb1)*50000;
data4(3,:) = (data2(3,:)./newc1)*50000;

v5=ProcAndPlot(data4);
%}


%grid
gridlim=80000;

[~,grid]=meshgrid(1:3,-gridlim:10:gridlim);
Xgrid=(grid*diag(V(:,1)));
Ygrid=(grid*diag(V(:,2)));
Zgrid=(grid*diag(V(:,3)));

Xgrid2=(grid*diag(V2(:,1)));
Ygrid2=(grid*diag(V2(:,2)));
Zgrid2=(grid*diag(V2(:,3)));

%V2(:,1)

figure(2)
hold on
plot3(Xgrid(:,1),Xgrid(:,2),Xgrid(:,3),'g');
plot3(Ygrid(:,1),Ygrid(:,2),Ygrid(:,3),'b');
plot3(Zgrid(:,1),Zgrid(:,2),Zgrid(:,3),'r');
hold off
figure(3)
hold on
plot3(Xgrid2(:,1),Xgrid2(:,2),Xgrid2(:,3),'g');
plot3(Ygrid2(:,1),Ygrid2(:,2),Ygrid2(:,3),'b');
plot3(Zgrid2(:,1),Zgrid2(:,2),Zgrid2(:,3),'r');
%}
hold off;



