# Philosophers 🧘‍♂️🍜
  
This project delves into concurrency, synchronization, and the classic dining philosophers problem, where each philosopher must think, eat, and avoid starving—all while managing shared resources.

## Table of Contents

- [Introduction](#introduction)
- [Challenge](#challenge)
- [Setup](#setup)
- [How It Works](#how-it-works)
- [Parameters](#parameters)
- [Execution](#execution)
- [Author](#author)

## Introduction

The **Philosophers** project, part of the [42 School](https://42.fr/) curriculum, is designed to understand threads, mutexes, and semaphore-based concurrency. Each philosopher has only two forks, and they must coordinate to avoid deadlocks and starvation.

The program simulates a group of philosophers seated around a circular table, alternating between thinking and eating. The challenge lies in ensuring that no two philosophers hold the same fork simultaneously while allowing everyone to dine without falling into a deadlock.

## Challenge

The **Dining Philosophers Problem** is a classic synchronization issue in computer science, exploring how processes can access shared resources safely. Here’s the setup:
- Philosophers need two forks to eat.
- If two philosophers pick up the same fork, or if all philosophers take their right fork, they’ll deadlock and be unable to continue.
- Efficiently managing resources and avoiding deadlock is the key goal.

## Setup

1. **Clone the repository**:
   ```bash
   git clone https://github.com/asut00/philosophers.git
   cd philosophers
   ```

2. **Compile the program**:
   ```bash
   make
   ```

3. This command generates an executable `philo`.

## How It Works

This project uses multiple threads to represent philosophers and mutexes to control fork access. The program observes the following rules:
- Each philosopher picks up the fork to their left and right in order to eat.
- If a philosopher cannot acquire both forks, they wait.
- After eating, the philosopher puts down both forks and returns to thinking.

Through careful synchronization, **Philosophers** ensures that no philosopher starves or causes a deadlock, as each philosopher cycles between eating and thinking states.

## Parameters

The program expects the following arguments:

```plaintext
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: Number of philosophers and forks (one fork per philosopher).
- `time_to_die`: Time (in ms) a philosopher can live without eating before dying.
- `time_to_eat`: Time (in ms) a philosopher spends eating.
- `time_to_sleep`: Time (in ms) a philosopher spends sleeping after eating.
- `number_of_times_each_philosopher_must_eat` *(optional)*: Total number of times each philosopher should eat before the simulation ends.

## Execution

To start the simulation, use the following command:

```bash
./philo 5 800 200 200
```

In this example:
- There are 5 philosophers.
- Each philosopher will die if they don’t eat within 800ms.
- Eating takes 200ms, and sleeping takes another 200ms.

If `number_of_times_each_philosopher_must_eat` is provided, the simulation ends when each philosopher has eaten that many times.

## Observing the Output

The program prints each philosopher's actions in real time, such as:

- `Philosopher 1 is thinking`
- `Philosopher 2 has taken a fork`
- `Philosopher 3 is eating`
- `Philosopher 4 is sleeping`

These logs help you monitor the philosophers' behavior and verify that there’s no deadlock or starvation.

## Author

- GitHub: [@asut00](https://github.com/asut00)  
- 42 Intra: `asuteau`
