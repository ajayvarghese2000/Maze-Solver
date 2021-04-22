clear all;
clc;

%open com port
ComPort = 'COM4';
[s,flag] = setupSerialRev2(ComPort,9600);


%increase max lim if data lies beyond the boundaries
max_lim = 80000;

iter=0;
while 1
    iter=iter+1;
    
    pitch=fscanf(s,'%f')
    roll=fscanf(s,'%f')
    
    
    %roll  = atan(y/ sqrt(x*x + z*z))
    %pitch = atan(y/ sqrt(y*y + z*z))

    
    %plot3(xyz(1),xyz(2),xyz(3),'ro')
    %plot3(x,y,z,'ro')
    floaty(3,pitch,roll)
     
    %xlim([-max_lim, max_lim])
    %ylim([-max_lim, max_lim])
    %zlim([-max_lim, max_lim])
    xlabel('X axis','FontSize',12,'Color','r')
    ylabel('Y axis','FontSize',12,'Color','g')
    zlabel('Z axis','FontSize',12,'Color','b')
    view(10,10);
    camorbit(iter,0,'data')
    drawnow; 
end
%fprintf(fID,endStr);

%if closeSerial() is never reached serial port
%needs to be closed manually by running the function
closeSerial();
fclose(fID);

function floaty(lim1,pitch,roll)
lim=[-lim1 lim1];


xlength=2;
ylength=1;
thiq=1;

tip=[xlength*cos(pitch),0,xlength*sin(pitch)];
wing=[0,ylength*cos(roll),ylength*sin(roll)];
wing2=[0,-ylength*cos(roll),-ylength*sin(roll)];
bum=[-thiq*cos(pitch),0,-thiq*sin(pitch)];

floatyobj=[tip;wing;bum;wing2;tip];

plot3(floatyobj(:,1),floatyobj(:,2),floatyobj(:,3),'r-o','LineWidth',2);
%axes(lim);
%view(0,0);
xlim(lim)
ylim(lim)
zlim(lim)
view(30,70);
grid on
end