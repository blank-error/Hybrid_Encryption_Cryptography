Hybrid_Encryption_Cryptography

Phase - 1: Hybrid Classical Encryption Algorithm
This phase of the project implements a custom hybrid encryption algorithm that combines two classical cryptographic techniques: monoalphabetic substitution and the Caesar cipher. Designed to increase complexity and security over traditional methods, the algorithm alternates between substitution and shifting operations while preserving non-alphabetic characters. The phase also includes a corresponding decryption algorithm to accurately recover the original plaintext.

Features
>Hybrid Encryption Logic: Encrypts using monoalphabetic substitution for every 6th character and Caesar cipher shifts for the following five characters.
>File-Based Processing: Reads input plaintext and outputs encrypted/decrypted text to files.
>Preserves Non-Alphabetic Characters: Spaces, punctuation, and symbols remain unchanged.
>Console Interface: Demonstrates step-by-step encryption and decryption processes.

Use Case
This phase of the project is ideal for educational purposes to understand classical encryption techniques and how combining them can enhance security.


Phase - 2: Cryptanalysis of Hybrid Classical Cipher
This phase of the project represents the second phase of a two-part cryptographic system, shifting focus from encryption to cryptanalysis. It implements automated frequency analysis techniques—single-letter, diagram (bigram), and trigram frequencies—to identify patterns in ciphertext encrypted using a custom hybrid classical cipher. A dictionary-based validation system is also included to match discovered word patterns with known vocabulary, aiding in the reconstruction of the original plaintext.

Features
>Frequency Analysis Tools: Identifies and reports the frequency of individual letters, bigrams, and trigrams in encrypted text.
>Dictionary Matching: Validates possible decrypted words against a built-in dictionary to improve accuracy.
>Automated Attack Strategy: Attempts to reverse-engineer ciphertext produced by the hybrid encryption from Phase 1.
>User Interaction: Allows users to interpret frequency data and explore potential plaintext outputs.

Purpose
Designed as an educational tool, this phase demonstrates how classical encryption techniques are vulnerable to pattern-based attacks and highlights the importance of eliminating predictable structures in secure cryptographic systems.
