# Covid-genoma-analysis

# Análise de Repetições no Genoma do Coronavírus e da dengue tipo 2

Este projeto realiza a análise de **blocos repetidos de 6 bases nitrogenadas** em arquivos contendo o genoma do Coronavírus (SARS-CoV-2). A contagem é feita apenas sobre **blocos consecutivos de 6 em 6 letras**, iniciando do começo de cada linha. Cada linha do genoma contém 60 caracteres (exceto a última, que é ignorada).

---

## Objetivo

O objetivo é contar quantas vezes cada **bloco de 6 bases** (como `ATTAAA`, `AGGTTT`, etc.) aparece no genoma, considerando apenas blocos extraídos **sem sobreposição**, a cada 6 caracteres.

Essa contagem é útil na **Biologia Molecular Computacional**, pois repetições em genomas podem estar relacionadas a **funções genéticas importantes** ou até **doenças genéticas**, como a Esclerose Lateral Amiotrófica (ELA).

---

## Entrada

- Arquivos `.txt` contendo o genoma em formato simples (ex: `sequences.fasta1.txt`, `sequences.fasta2.txt`).
- Cada linha do arquivo deve conter **exatamente 60 letras (A, T, C, G)**. A última linha é ignorada se tiver menos de 60 caracteres.

---

## Saída

Para cada arquivo de entrada, é gerado um arquivo `.txt` com duas colunas:
1. O bloco de 6 letras.
2. O número de vezes que esse bloco aparece no genoma.

Exemplo de saída:

ATTAAA 3
AGGTTT 1


##  Como Funciona

O programa utiliza uma **tabela de espalhamento (hash table)** com:
- **Função de hash multiplicativa** baseada em `hash = hash * 31 + c`
- **Encadeamento externo** (listas ligadas) para tratar colisões

### Componentes principais:
- `NoHash`: representa um nó com o bloco e a contagem.
- `TabelaHash`: estrutura de hash com vetor de ponteiros e métodos de inserção e gravação.
- `processarArquivo`: lê o arquivo de genoma, extrai os blocos e atualiza a tabela.
- `main`: executa o processamento de dois arquivos de entrada e salva os resultados.



