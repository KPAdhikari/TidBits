//
//  EditView.swift
//  Scrumdinger
//
//  Created by Krishna Adhikari on 8/12/21.
//

import SwiftUI

struct EditView: View {
    //@State private var scrumData: DailyScrum.Data = DailyScrum.Data()
    @Binding var scrumData: DailyScrum.Data //= DailyScrum.Data()
    @State private var newAttendee = ""
    var body: some View {
        //Text("Hello World")
        List {
            Section(header: Text("Meeting Info")) {
                TextField("Title", text: $scrumData.title)
                HStack {
                    Slider(value: $scrumData.lengthInMinutes, in: 5...30, step: 1.0) {
                        Text("Length")
                    }
                    .accessibilityValue(Text("\(Int(scrumData.lengthInMinutes)) minutes"))
                    Spacer()
                    Text("\(Int(scrumData.lengthInMinutes)) minutes")
                        .accessibilityHidden(true)
                }
                
                ColorPicker("Color", selection: $scrumData.color)
                    .accessibilityLabel(Text("Color picker"))
                //The color picker has the “button” accessibility trait, so don’t include the word “button” in the label.
            }
            Section(header: Text("Attendees")) {
                ForEach(scrumData.attendees, id: \.self) { attendee in
                    Text(attendee)
                }
                .onDelete { indices in
                    scrumData.attendees.remove(atOffsets: indices)
                }
                HStack {
                    TextField("New Attendee", text: $newAttendee)
                    Button(action: {
                        withAnimation {
                            scrumData.attendees.append(newAttendee)
                        }
                        newAttendee = ""
                    }) {
                        Image(systemName: "plus.circle.fill")
                            .accessibilityLabel(Text("Add attendee"))
                    }
                    .disabled(newAttendee.isEmpty) //kp: Disable the button if newAttendee is empty.
                    //     The button will activate when the user types a name in the text field.
                }
            }
        }
        .listStyle(InsetGroupedListStyle())
    }
}

struct EditView_Previews: PreviewProvider {
    static var previews: some View {
        //EditView()
        EditView(scrumData: .constant(DailyScrum.data[0].data))
    }
}
