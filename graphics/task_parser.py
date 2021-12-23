from collections import defaultdict


def read_tasks(file_name: str) -> list[tuple[int, int, int]]:
    with open(file_name, 'r', encoding='utf-8') as fin:
        _ = fin.readline()
        text_tasks = fin.readline()
        tasks = []
        for task in text_tasks.split(';')[:-1]:
            agent_id, location, timestamp = task.split(',')
            agent_id = int(agent_id)
            location = int(location)
            timestamp = int(timestamp) if timestamp != '' else 0
            tasks.append((agent_id, location, timestamp))
    return tasks


def group_tasks_by_timestamps(tasks: list[tuple[int, int, int]]) -> list[int, int]:
    grouped_tasks = defaultdict(int)
    for task in tasks:
        if task[2] != 0:
            grouped_tasks[task[2]] += 1
    return sorted(grouped_tasks.items(), key=lambda x: x[0])


def read_paths(file_name: str, width: int, height: int) -> list[list[tuple[int, int]]]:
    with open(file_name, 'r', encoding='utf-8') as fin:
        _ = fin.readline()
        text_paths = fin.readlines()
        paths = []
        for agent_id, text_path in enumerate(text_paths):
            path = []
            for text_step in text_path.split(';')[:-1]:
                location, _, timestamp = task.split(',')
                location = int(location)
                timestamp = int(timestamp)
                path.append(location_to_coords(location, width, height))
            paths.append(path)
    return paths


def location_to_coords(location: int, width: int, height: int) -> tuple[int, int]:
    return location % width, location // height