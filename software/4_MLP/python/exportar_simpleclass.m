% Exporta el dataset oficial de MathWorks para entrenarlo desde Python.
% Requiere MATLAB con Deep Learning Toolbox.

[entradas, objetivos] = simpleclass_dataset;
clases = vec2ind(objetivos) - 1;

datos = [entradas.' clases.'];
ruta = fullfile(fileparts(mfilename('fullpath')), 'simpleclass.csv');
writematrix(datos, ruta);

fprintf('Dataset exportado en: %s\n', ruta);
fprintf('Forma de entradas: %d x %d\n', size(entradas, 1), size(entradas, 2));
fprintf('Forma de objetivos: %d x %d\n', size(objetivos, 1), size(objetivos, 2));
fprintf('Muestras por clase: %d %d %d %d\n', ...
    sum(clases == 0), sum(clases == 1), ...
    sum(clases == 2), sum(clases == 3));
