clear all
clc
lim=[-2 2];

origin=[0,0,0];
tip=[2,0,1];
lwing=[0,1,0];
vecMag = [origin;tip;lwing;origin];


vecAcc = [0,0,0;0,0,-1];
pitch=atan(vecAcc(2,3)/vecAcc(2,1));
 

hold on
grid on
plot3(vecMag(:,1),vecMag(:,2),vecMag(:,3),'r','LineWidth',2)
plot3(vecAcc(:,1),vecAcc(:,2),vecAcc(:,3),'b','LineWidth',2)
xlim(lim)
xlabel('x-axis')
ylim(lim)
ylabel('y-axis')
zlim(lim)
zlabel('z-axis')
axes(lim)
hold off


function axes(lim)

plot3([lim(1) lim(2)],[0 0],[0 0],'k')
plot3([0 0],[lim(1) lim(2)],[0 0],'k')
plot3([0 0],[0 0],[lim(1) lim(2)],'k')

end