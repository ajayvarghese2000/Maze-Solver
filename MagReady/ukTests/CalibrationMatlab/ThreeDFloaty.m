clear all
clc
lim=[-3 3];
pitch = 0.5;
roll = -0.5;

xlength=2;
ylength=1;
thiq=1;

tip=[xlength*cos(pitch),0,xlength*sin(pitch)];
wing=[0,ylength*cos(roll),ylength*sin(roll)];
wing2=[0,-ylength*cos(roll),-ylength*sin(roll)];
bum=[-thiq*cos(pitch),0,-thiq*sin(pitch)];

floaty=[tip;wing;bum;wing2;tip];

plot3(floaty(:,1),floaty(:,2),floaty(:,3));
%axes(lim);
%view(0,0);
xlim([-3 3])
ylim([-3 3])
zlim([-3 3])
grid on

%{
function axes(lim)

plot3([lim(1) lim(2)],[0 0],[0 0],'k')
plot3([0 0],[lim(1) lim(2)],[0 0],'k')
plot3([0 0],[0 0],[lim(1) lim(2)],'k')

end
%}