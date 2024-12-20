#include "ship.h"

void Ship::damage_segment(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Segment index out of range.");
    }

    if(mark_hidden_damage[index] == damaged_state) {
        segments[index] = destroyed_state;
    } else {
        if (segments[index] == whole_state) {
            segments[index] = damaged_state;
        } else if (segments[index] == damaged_state) {
            segments[index] = destroyed_state;
        }
    }
}

int Ship::get_segment_state(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Segment index out of range.");
    }
    return segments[index];
}

bool Ship::is_destroy() {
    int destroy_segments = 0;
    for(int i = 0; i < length; i++) {
        int state = get_segment_state(i);
        if(state == destroyed_state) destroy_segments += 1;
    }
    if(destroy_segments == length) return true;
    else return false;
}

void Ship::damage_secret_segment(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Segment index out of range.");
    }
    if(mark_hidden_damage[index] == damaged_state) {
        damage_segment(index);
    }
    mark_hidden_damage[index] = damaged_state;
}

void Ship::set_segment_state(int index, int value) {
    if(value == 0)
        segments[index] = whole_state;
    if(value == 1)
        segments[index] = damaged_state;
    if(value == 2)
        segments[index] = destroyed_state;
}