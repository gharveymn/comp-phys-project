fileID = fopen('map.txt', 'r');
formatSpec = '%f';
data = fscanf(fileID,formatSpec);
a = 0;
x_min = data(1);
x_max = data(2);
y_min = data(3);
y_max = data(4);
num_sqares = data(5);
axis([x_min x_max y_min y_max]);

for i=6:3:size(data,1) - 2
    x = data(i) - data(i+2)/2;
    y = data(i+1) - data(i+2)/2;
    w = data(i+2);
    rectangle('Position', [x y w w]);
end;