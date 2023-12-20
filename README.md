# Multilevel Queue CPU Scheduling Simulation

## Overview

This module simulates Multilevel Queue (MLQ) CPU Scheduling, which is designed to address the issue of CPU starvation for certain processes when higher-priority queues are continuously occupied.

## Usage

1. **Compilation:**
    gcc mlq_scheduler.c -o mlq_scheduler.exe

2. **Execution:**
    mlq_scheduler.exe

## Input

The program prompts the user to enter information for each process, including the number of processes, burst time, and process type (system or user).

## Functionality

- **multilevelQueueScheduling Function:**
  - Orchestrates the MLQ scheduling algorithm, including aging mechanisms, process distribution, and time tracking.

## Output and Results Presentation

The results of the multilevel queue scheduling are presented in a tabular format, showcasing process ID, process type, burst time, waiting time, and turnaround time.
