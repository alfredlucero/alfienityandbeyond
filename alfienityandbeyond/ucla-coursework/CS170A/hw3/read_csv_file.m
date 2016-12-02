function csvData = read_csv_file(urlString) 

    dataStr = urlread(urlString);
    dataStr = strsplit(dataStr, '\n');
    dimRows = size(dataStr);
    rows = dimRows(1,2) - 1;
    dataStrOne = strsplit(char(dataStr(1)), ';\s*', 'DelimiterType', 'RegularExpression');
    dataDim = size(dataStrOne); 
    cols = dataDim(1,2);
    dataMatrix = zeros(rows, cols);
    for i = 1:rows
       dataMatrix(i,:) = str2double(strsplit(char(dataStr(i)), ';\s*', 'DelimiterType','RegularExpression'));
    end
    
    csvData = dataMatrix;
end