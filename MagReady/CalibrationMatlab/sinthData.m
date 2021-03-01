clear all;
clc;
%generates noisy data

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

dx=xx(:); dy=yy(:); dz=zz(:);

predata=[dx,dy,dz];
fID = fopen('sinthdata.txt','w');
fprintf(fID,'%f\t%f\t%f\n',predata');
fclose(fID);

textFile = 'sinthdata.txt';
fID2 = fopen(textFile,'r');
data = fscanf(fID2,'%f\t%f\t%f',[3,inf]);
fclose(fID2);

x1=data(1,:)';
y1=data(2,:)';
z1=data(3,:)';

figure(1)
plot3(data(1,:),data(2,:),data(3,:),'ko')
xlim([-max_lim max_lim])
ylim([-max_lim max_lim])
zlim([-max_lim max_lim])

figure(2)
plot3(dx,dy,dz,'ro')
xlim([-max_lim max_lim])
ylim([-max_lim max_lim])
zlim([-max_lim max_lim])

