clear all
clc
ComPort = 'COM4';
[s,flag] = setupSerial(ComPort);

a=0;

%twat=readOut(s,1000);
while true
    a=a+1;
    %fscanf(s,'%f')
    if rem(a,200)==0
        plot(a,fscanf(s,'%f'),'bo')
        axis([a-500 a+500 -1.5 1.5]);
    end
    drawnow
    
end
figure(1);






closeSerial()
plot(1:1000,twat,'b--');
function y=readOut(x,d)
y=zeros([1,d]);
    for i=1:d
        y(i)=fscanf(x,'%f');
        %fscanf(x,'%f')
    end


end

