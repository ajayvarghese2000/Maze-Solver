clear all;
clc;

%open com port
ComPort = 'COM4';
[s,flag] = setupSerialRev2(ComPort,28800);

%number of data samples to be collected
dataAmount = 20000;
offset=800;
%increase max lim if data lies beyond the boundaries
max_lim = 100000;

%iteration counter
iter=0;

fID = fopen('test3.txt','w');

figure(1)

xyz=zeros(offset,3);
n=0;
view(30,30);
while iter < dataAmount
    iter=iter+1;
    sprintf("%f",iter)
    
    x=fscanf(s,'%f');
    y=fscanf(s,'%f');
    z=fscanf(s,'%f');
    xyz(iter-n,:)=[x,y,z];
    if ~mod(iter,offset)
        n=n+offset;
    end
    fprintf(fID,'%.7f\t%.7f\t%.7f\n',x,y,z);
    %hold on

    plot3(xyz(:,1),xyz(:,2),xyz(:,3),'ro')
     
    xlim([-max_lim, max_lim])
    ylim([-max_lim, max_lim])
    zlim([-max_lim, max_lim])
    xlabel('X axis','FontSize',12,'Color','r')
    ylabel('Y axis','FontSize',12,'Color','g')
    zlabel('Z axis','FontSize',12,'Color','b')

    camorbit(iter,0,'data')
    %{
    if ~mod(iter,800)
        clf(1); 
        view(30,30);
    
    end
    %}
    drawnow; 
end
%fprintf(fID,endStr);

%if closeSerial() is never reached serial port
%needs to be closed manually by running the function
closeSerial();
fclose(fID);