import pandas as pd
import re
import plotly.express as px

# Função para ler tempos médios de cada arquivo
def read_and_process_file(filename):
    with open(filename, "r") as file:
        content = file.read()
    # Extrair tempos médios por tamanho de matriz
    pattern = r"Matrix size: (\d+), Time spent: ([\d.]+) seconds"
    matches = re.findall(pattern, content)
    times = {}
    for size, time in matches:
        size = int(size)
        time = float(time)  # Tempo já em segundos
        if size not in times:
            times[size] = []
        times[size].append(time)
    # Calcular a média dos tempos
    avg_times = {size: sum(times[size]) / len(times[size]) for size in times}
    return avg_times

# Lista de arquivos e códigos
filenames = [f"execution_times_cod{i+1}.txt" for i in range(5)]
codes = [f"Código {i+1}" for i in range(5)]

# Ler dados de todos os arquivos
data = []
matrix_sizes = set()  # Para armazenar todos os tamanhos de matriz encontrados
for code, filename in zip(codes, filenames):
    avg_times = read_and_process_file(filename)
    for size, avg_time in avg_times.items():
        # Calcular GFLOPS usando a fórmula
        gflops = (2 * (size ** 3)) / (avg_time * 1e9)
        data.append({"Código": code, "Tamanho da Matriz": f"{size}x{size}", "GFLOPS": gflops})
        matrix_sizes.add(f"{size}x{size}")

# Converter para DataFrame
df = pd.DataFrame(data)

# Criar gráfico de barras agrupadas
fig = px.bar(
    df,
    x="Código",
    y="GFLOPS",
    color="Tamanho da Matriz",
    barmode="group",  # Barras agrupadas lado a lado
    title="Performance em GFLOPS por Código e Tamanho da Matriz",
    labels={"GFLOPS": "Performance (GFLOPS)", "Código": "Código"}
)

# Adicionar valores acima das barras com 3 casas decimais
fig.for_each_trace(lambda trace: trace.update(
    text=df[df["Tamanho da Matriz"] == trace.name]["GFLOPS"].apply(lambda x: f"{x:.3f}"),  # Exibe 3 casas decimais
    textposition="outside"  # Posição do texto acima das barras
))

# Melhorar layout do gráfico
fig.update_layout(
    xaxis_title="Código",
    yaxis_title="Performance (GFLOPS)",
    legend_title="Tamanho da Matriz",
    template="plotly_white",
    bargap=0.2  # Espaçamento entre grupos de barras
)

fig.show()
