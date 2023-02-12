import csv

def process_row(row):
    # Preencher cada linha com asteriscos até 20 caracteres
    row = [content.ljust(19, '*') for content in row]
    return row

# Abrir arquivo CSV de entrada para leitura
with open('dataset.csv', 'r') as input_file:
    reader = csv.reader(input_file)
    # Abrir arquivo CSV de saída para escrita
    with open('dataset_formatado.csv', 'w', newline='') as output_file:
        writer = csv.writer(output_file)
        # Processar cada linha do arquivo CSV de entrada
        for row in reader:
            processed_row = process_row(row)
            writer.writerow(processed_row)