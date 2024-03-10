#include "frequency_map.h"

NoteIdx CurrentNote(float frequency)
{
    auto semitones = 12 * std::log2f(frequency / kReferenceFrequency);
    auto idx = static_cast<int>(std::roundf(semitones)) + 9;
    auto note_idx = idx % 12;
    note_idx = note_idx < 0 ? 12 + note_idx : note_idx;
    auto oct_idx = static_cast<float>(idx) / 12;
    oct_idx = oct_idx < 1 ? std::floor(oct_idx) : std::ceil(oct_idx);
    auto octave = 4 + (oct_idx);
    return NoteIdx{
        .note = static_cast<Note>(note_idx),
        .octave = static_cast<int>(octave),
        .freq = frequency,
    };
}

int GetNoteDiff(Note note)
{
    int diff = 0;
    switch (note)
    {
    case Note::A_sharp:
        diff = 1;
        break;
    case Note::B:
        diff = 2;
        break;
    case Note::C:
        diff = -9;
        break;
    case Note::C_sharp:
        diff = -8;
        break;
    case Note::D:
        diff = -7;
        break;
    case Note::D_sharp:
        diff = -6;
        break;
    case Note::E:
        diff = -5;
        break;
    case Note::F:
        diff = -4;
        break;
    case Note::F_sharp:
        diff = -3;
        break;
    case Note::G:
        diff = -2;
        break;
    case Note::G_sharp:
        diff = -1;
        break;
    default:
        break;
    }
    return diff;
}

float GetFrequency(NoteIdx note)
{
    auto semitones_from_ref = GetNoteDiff(note.note) + (note.octave - 4) * 12;
    return kReferenceFrequency * std::pow(2.0, semitones_from_ref / 12.0);
}

NoteLimit GetNoteLimits(NoteIdx note)
{
    auto freq = GetFrequency(note);
    // auto factor = std::pow(2.0, 0.5 / 12.0) - 1;
    constexpr double factor = 0.0293022366434921 * 0.5;
    auto delta_semi = std::log2(std::abs(note.freq / freq)) * 12.0;
    auto interpolated_val = std::pow(2.0, std::abs(delta_semi) / 12) - 1;
    auto delta = note.freq - freq;
    auto actual = interpolated_val / factor;
    if (delta < 0)
    {
        actual = 0.5 - (actual - 0.5);
    }

    auto lower = freq / factor;
    auto higher = freq * factor;
    return NoteLimit{
        .lower = static_cast<float>(lower),
        .higher = static_cast<float>(higher),
        .scalar = static_cast<float>(actual),
    };
}