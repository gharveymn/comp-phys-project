fileID = fopen('map.txt', 'r');
formatSpec = '%f';
data = fscanf(fileID,formatSpec);
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
    rectangle('Position', [x y w w], 'FaceColor', [0 0 1]);
end;

fileID = fopen('tree.txt', 'r');
formatSpec = '%f';
data = fscanf(fileID, formatSpec);

for i=1:4:size(data,1)
    x = data(i);
    y = data(i + 1);
    l = data(i + 2);
    w = data(i +3);
    rectangle('Position', [x y l w]);
end;