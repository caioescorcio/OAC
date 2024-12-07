from plotly import express as px
import re
import numpy as np

# Leitura dos dados
times = []
for i in range(5):
    filename = f"cod{i+1}_time.txt"
    with open(filename, "r") as f:
        times.append(f.read())

# Extrair tempo
def extract_time(time: str):
    time = time.split("\n")
    time = [float(_time)/1000 for _time in time[:-1]]
    return time

# Extrair tempo
times = [extract_time(time) for time in times]
x=[f"Código {i+1}" for i in range(len(times))]
times_dict = {f"Código {i+1}": time for i, time in enumerate(times)}

# Gráfico (scatter)
fig = px.scatter(times_dict, title="Tempo de execução dos códigos", labels={"x": "Código", "y": "Tempo (us)"}, orientation="v")

fig.update_layout(
    xaxis_title="Iteração",
    yaxis_title="Tempo de Execução (us)",
)

# marker
fig.update_traces(marker=dict(size=20)) 
fig.show()

# Gráfico (barra)
px.bar(x = list(times_dict.keys()), y=np.average(list(times_dict.values()), axis=1),
       title="Tempo de execução dos códigos", orientation="v",
       labels={"x": "Código", "y": "Tempo médio (us)"}).show()


