TARGET = index.pdf
SOURCE = index.tex
INTERMEDIATE_FILES = */*.aux *.aux *.swp *.log *.toc .*.swp
LATEX = xelatex

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(LATEX) $(SOURCE)

clean:
	rm -f $(TARGET) $(INTERMEDIATE_FILES)

clean-intermediate:
	rm -f $(INTERMEDIATE_FILES)

.PHONY: all clean clean-intermediate
