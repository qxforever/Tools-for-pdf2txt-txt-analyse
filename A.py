import pdfplumber

ms = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December']

for year in range(2004, 2014) :
    for month in ms :
        s = '01pdf\\' + month + str(year) + 'ChiefsDirectory'
        with open(s + '.txt', 'w', encoding = "utf-8") as fw:
            print('...')
            with pdfplumber.open(s + '.pdf') as pdf:
                for page in pdf.pages:
                    fw.write(page.extract_text())