from pdfminer.pdfparser import PDFParser, PDFDocument
from pdfminer.pdfinterp import PDFResourceManager, PDFPageInterpreter
from pdfminer.converter import PDFPageAggregator
from pdfminer.layout import LTTextBoxHorizontal, LAParams
from pdfminer.pdfinterp import PDFTextExtractionNotAllowed

device = PDFPageAggregator(PDFResourceManager(), laparams=LAParams())
interpreter = PDFPageInterpreter(PDFResourceManager(), device)

ms = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December']

for year in range(2006, 2014) :
    for month in ms :
        s = '01pdf\\' + month + str(year) + 'ChiefsDirectory'
        pdf_filename = s + '.pdf'
        txt_filename = s + '_.txt'
        doc = PDFDocument()
        parser = PDFParser(open(pdf_filename, 'rb'))
        parser.set_document(doc)
        doc.set_parser(parser)
        doc.initialize()

        # 检测文档是否提供 txt 转换，不提供就忽略
        if not doc.is_extractable:
            raise PDFTextExtractionNotAllowed
        else:
            with open(txt_filename, 'w', encoding = "utf-8") as fw:
                print("num page:{}".format(len(list(doc.get_pages()))))
                for page in doc.get_pages():
                    interpreter.process_page(page)
                    # 接受该页面的 LTPage 对象
                    layout = device.get_result()
                    # 这里 layout 是一个 LTPage 对象 里面存放着 这个 page 解析出的各种对象
                    # 一般包括 LTTextBox, LTFigure, LTImage, LTTextBoxHorizontal 等等
                    # 想要获取文本就获得对象的text属性，
                    for x in layout:
                        if isinstance(x, LTTextBoxHorizontal):
                            results = x.get_text()
                            fw.write(results)