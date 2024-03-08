#pragma once

#include <cmath>
#include <cstdint>

enum class Note : std::uint8_t
{
    C = 0,
    C_sharp,
    D,
    D_sharp,
    E,
    F,
    F_sharp,
    G,
    G_sharp,
    A,
    A_sharp,
    B,
};

int GetNoteDiff(Note note);

struct NoteContainer
{
    Note note;
    float current;
};

struct NoteIdx
{
    Note note;
    int octave;
    float freq;
};

struct NoteLimit
{
    float lower;
    float higher;
    float scalar;
};

constexpr double kReferenceFrequency = 440.0;

// float GetLowerBoundary();
// float GetUpperBoundary();
NoteIdx CurrentNote(float frequency);
float GetFrequency(NoteIdx note);
NoteLimit GetNoteLimits(NoteIdx note);
