import sys
import queue

class Process:
    def __init__(self, name, priority, arrival_time, total_time, block_interval):
        self.name = name
        self.priority = priority
        self.arrival_time = arrival_time
        self.total_time = total_time
        self.block_interval = block_interval
        self.remaining_time = total_time
        self.time_until_block = block_interval if block_interval > 0 else total_time  # If never blocks, set very large
        self.blocked_until = None
        self.start_time = None
        self.completion_time = None
        self.last_run_time = -1  # Track when it last ran for round-robin

    def __lt__(self, other):
        # Sort by priority, then longest wait (lowest last_run_time), then arrival time
        if self.priority != other.priority:
            return self.priority > other.priority
        if self.last_run_time != other.last_run_time:
            return self.last_run_time < other.last_run_time
        return self.arrival_time < other.arrival_time

def parse_input_file(filename):
    processes = []
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            parts = line.split()
            name, priority, arrival, total_time, block_interval = parts[0], int(parts[1]), int(parts[2]), int(parts[3]), int(parts[4])
            processes.append(Process(name, priority, arrival, total_time, block_interval))
    return processes

def run_scheduler(process_list, time_slice, block_duration):
    arrival_queue = queue.PriorityQueue()
    blocked_queue = queue.PriorityQueue()
    ready_list = []

    for process in process_list:
        arrival_queue.put((process.arrival_time, process))

    current_time = 0
    intervals = []

    def move_arrivals():
        while not arrival_queue.empty() and arrival_queue.queue[0][0] <= current_time:
            _, proc = arrival_queue.get()
            ready_list.append(proc)

    def move_unblocked():
        while not blocked_queue.empty() and blocked_queue.queue[0][0] <= current_time:
            _, proc = blocked_queue.get()
            # Reset time_until_block unless never blocks
            proc.time_until_block = proc.block_interval if proc.block_interval > 0 else proc.remaining_time
            ready_list.append(proc)

    while not arrival_queue.empty() or not blocked_queue.empty() or ready_list:
        move_arrivals()
        move_unblocked()

        if not ready_list:
            # Idle if nothing to do
            next_event = None
            if not arrival_queue.empty():
                next_event = arrival_queue.queue[0][0]
            if not blocked_queue.empty():
                unblock_time = blocked_queue.queue[0][0]
                next_event = min(next_event, unblock_time) if next_event is not None else unblock_time

            if next_event is None:
                break  # No more events

            idle_interval = next_event - current_time
            if idle_interval > 0:
                intervals.append((current_time, "(IDLE)", idle_interval, "I"))
            current_time = next_event
            continue

        # Sort ready list by priority and last run time for fair round-robin
        ready_list.sort()
        proc = ready_list.pop(0)

        run_length = min(time_slice, proc.time_until_block, proc.remaining_time)
        if proc.start_time is None:
            proc.start_time = current_time

        # Process runs
        intervals.append((current_time, proc.name, run_length, "R"))
        current_time += run_length
        proc.remaining_time -= run_length
        proc.time_until_block -= run_length
        proc.last_run_time = current_time

        move_arrivals()
        move_unblocked()

        if proc.remaining_time == 0:
            proc.completion_time = current_time
            intervals[-1] = (intervals[-1][0], proc.name, run_length, "T")
        elif proc.block_interval > 0 and proc.time_until_block == 0:
            proc.blocked_until = current_time + block_duration
            blocked_queue.put((proc.blocked_until, proc))
            intervals[-1] = (intervals[-1][0], proc.name, run_length, "B")
        else:
            ready_list.append(proc)
            intervals[-1] = (intervals[-1][0], proc.name, run_length, "P")

    total_turnaround = sum(proc.completion_time - proc.arrival_time for proc in process_list)
    avg_turnaround = total_turnaround / len(process_list)

    print(f"timeSlice: {time_slice}\tblockDuration: {block_duration}")
    for start, name, length, code in intervals:
        print(f"{start}\t{name}\t{length}\t{code}")
    print(f"Average turnaround time: {avg_turnaround}")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python3 scheduler.py <input_file> <time_slice> <block_duration>")
        sys.exit(1)

    input_file = sys.argv[1]
    time_slice = int(sys.argv[2])
    block_duration = int(sys.argv[3])

    processes = parse_input_file(input_file)
    run_scheduler(processes, time_slice, block_duration)
