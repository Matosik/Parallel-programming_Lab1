import matplotlib.pyplot as plt

def parse_results(filename):
    sizes = []
    times = []
    with open(filename, 'r') as file:
        for line in file:
            # Извлекаем размер матрицы, который находится между словами "size" и "time"
            size = int(line.split('size')[1].split('x')[0])
            # Извлекаем время, которое находится между дефисом "-" и "ms"
            time = int(line.split('-')[1].strip().split('ms')[0].strip())
            sizes.append(size)
            times.append(time)
    return sizes, times


def plot_results(sizes, times):
    #plt.figure(figsize=(5, 5))
    plt.plot(sizes, times, marker='o')
    plt.title('Зависимость времени вычисления от размера матрицы')
    plt.xlabel('Размер матрицы (n x n)')
    plt.ylabel('Время (мс)')
    plt.grid(True)
    plt.show()

# Используйте название файла, в который вы сохраняете результаты
filename = 'data/ResultExperiment.txt'
sizes, times = parse_results(filename)
plot_results(sizes, times)
