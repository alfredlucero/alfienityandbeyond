function top_ten_notes = note_power(power, Fs)
    C_note = 131;
    c = 2^(1/12);
    equal_tempered_notes = zeros(61,1);
    equal_tempered_notes(1,1) = C_note;
    for i = 1:60
        equal_tempered_notes(i+1, 1) = C_note * c^i;
    end

    max_notes_within_div_lines = zeros(61,2);
    for i = 1:61
        if (i == 1) % first note only has above dividing line
            above_delta = (equal_tempered_notes(i, 1) + equal_tempered_notes(i+1, 1)) / 2;
            pos_vector = find(Fs >= equal_tempered_notes(1,1) & Fs <= above_delta );
            % Given the positions of the note frequencies, find the max power in the range of dividing lines
            max_power = 0;
            max_frequency = 0;
            for j=1:length(pos_vector)
                current_power = power(pos_vector(j));
                current_frequency = Fs(pos_vector(j));
                if (current_power > max_power)
                    max_power = current_power;
                    max_frequency = current_frequency;
                end
            end
            max_notes_within_div_lines(i,1) = max_power;
            max_notes_within_div_lines(i,2) = max_frequency;
        elseif (i == 61) % last note only has below dividing line
             below_delta = (equal_tempered_notes(i-1, 1) + equal_tempered_notes(i, 1)) / 2;
             pos_vector = find(Fs > below_delta & Fs <= equal_tempered_notes(i, 1) ); 
             % Given the positions of the note frequencies, find the max power in the range of dividing lines
            max_power = 0;
            max_frequency = 0;
            for j=1:length(pos_vector)
                current_power = power(pos_vector(j));
                current_frequency = Fs(pos_vector(j));
                if (current_power > max_power)
                    max_power = current_power;
                    max_frequency = current_frequency;
                end
            end
            max_notes_within_div_lines(i,1) = max_power;
            max_notes_within_div_lines(i,2) = max_frequency;
        else % the rest of the notes have above and below dividing lines
            above_delta = (equal_tempered_notes(i, 1) + equal_tempered_notes(i+1, 1)) / 2;
            below_delta = (equal_tempered_notes(i-1, 1) + equal_tempered_notes(i, 1)) / 2;
            pos_vector = find(Fs > below_delta & Fs <= above_delta );
            % Given the positions of the note frequencies, find the max power in the range of dividing lines
            max_power = 0;
            max_frequency = 0;
            for j=1:length(pos_vector)
                current_power = power(pos_vector(j));
                current_frequency = Fs(pos_vector(j));
                if (current_power > max_power)
                    max_power = current_power;
                    max_frequency = current_frequency;
                end
            end
            max_notes_within_div_lines(i,1) = max_power;
            max_notes_within_div_lines(i,2) = max_frequency;
        end
    end
    % Sort the notes according to highest power in ascending order (last 10 are top ten notes)
    sorted_max_notes = sortrows(max_notes_within_div_lines,1);
    top_ten_notes = sorted_max_notes(52:61, 2);
    

end