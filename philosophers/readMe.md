# Philosophers

> 🍝 Simulation du problème des philosophes avec gestion fine des threads et mutex  
> 🍝 Dining Philosophers problem simulation with precise thread and mutex handling

---

## 🇫🇷 À propos

Le projet **Philosophers** est une introduction aux problèmes de concurrence dans les systèmes multi-threadés.  
L'objectif est de simuler des philosophes assis autour d'une table, partageant des fourchettes pour manger, tout en **évitant les conditions de course**, les **deadlocks** et les **starvations**.

Ce projet m’a permis de maîtriser les bases du **multi-threading en C**, la synchronisation avec **mutex**, et la gestion précise du **temps et des accès concurrents**.

---

## 🇬🇧 About

**Philosophers** is an introduction to concurrency problems in multi-threaded systems.  
The goal is to simulate philosophers sitting around a table, sharing forks to eat, while **avoiding race conditions**, **deadlocks**, and **starvation**.

This project helped me master the fundamentals of **multi-threading in C**, synchronization with **mutexes**, and precise **time and concurrent access** management.

---

## 📜 Règles du jeu / Rules

- Chaque philosophe pense, mange, dort, puis recommence.
- Pour manger, il doit avoir **deux fourchettes** (la sienne et celle de gauche/droite).
- Il ne peut pas **mourir de faim** (doit manger avant un temps `time_to_die`).
- L'exécution se termine si :
  - Un philosophe meurt
  - Tous les philosophes ont mangé un nombre de fois donné (optionnel)

---

## ⚙️ Paramètres

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
