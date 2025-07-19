# push_swap

> 📦 Tri optimisé avec deux piles et un jeu d'instructions restreint  
> 📦 Optimized sorting using two stacks and a limited instruction set

---

## 🇫🇷 À propos

`push_swap` est un projet algorithmique du tronc commun de l'école 42.  
Le but est de trier une pile d'entiers en utilisant uniquement un ensemble restreint d'opérations sur deux piles (`a` et `b`). Le programme doit générer la **liste la plus courte possible d'instructions** pour effectuer ce tri.

Dans ce projet, j’ai mis en œuvre une stratégie appelée **chunk sort** pour optimiser les mouvements et réduire le nombre total d'opérations.

---

## 🇬🇧 About

`push_swap` is an algorithmic project from the 42 Common Core curriculum.  
The goal is to sort a stack of integers using only a limited set of operations on two stacks (`a` and `b`). The program must output the **shortest possible list of instructions** to achieve the sorted state.

For this project, I implemented a **chunk sort** strategy to minimize the number of moves and improve performance on large inputs.

---

## 🔧 Instructions disponibles / Allowed Instructions

| Instruction         | Description                             |
|---------------------|-----------------------------------------|
| `sa`, `sb`, `ss`    | Swap top elements of `a`, `b`, or both  |
| `pa`, `pb`          | Push top from `b` to `a`, or `a` to `b` |
| `ra`, `rb`, `rr`    | Rotate up `a`, `b`, or both             |
| `rra`, `rrb`, `rrr` | Reverse rotate down `a`, `b`, or both   |

---

## 🧠 Algorithme : Chunk Sort

### Principe

- La pile est divisée en **n chunks** (tranches de valeurs triées)
- On pousse les éléments de chaque chunk dans `b`, en priorisant leur positionnement
- Puis on les ramène dans `a` dans l’ordre en effectuant des rotations optimisées

### Avantages

- Excellente scalabilité pour les grands ensembles (> 100 nombres)
- Réduction significative du nombre d'opérations comparé à un tri naïf
- Facile à adapter selon le nombre total d'éléments (5, 100, 500...)

