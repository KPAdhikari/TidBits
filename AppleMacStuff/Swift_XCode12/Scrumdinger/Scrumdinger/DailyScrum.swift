//
//  DailyScrum.swift
//  Scrumdinger
//
//  Created by Krishna Adhikari on 8/9/21.
//

//import Foundation
import SwiftUI

//kp: adding a structure of type DailyScrum with following 4 properties.
struct DailyScrum: Identifiable {
    let id: UUID
    var title: String
    var attendees: [String]
    var lengthInMinutes: Int
    var color: Color

    //kp: Adding an initializer that assigns a default value to the id property.
    init(id: UUID = UUID(), title: String, attendees: [String],
         lengthInMinutes: Int, color: Color) {
        self.id = id
        self.title = title
        self.attendees = attendees
        self.lengthInMinutes = lengthInMinutes
        self.color = color
    }
}

//kp: adding an extension that provides some test data.
//The starting project includes the random static property on Color.
extension DailyScrum {
    static var data: [DailyScrum] {
        [
            DailyScrum(title: "Design", attendees: ["Cathy", "Daisy", "Simon", "Jonathan"], lengthInMinutes: 10, color: Color("Design")),
            DailyScrum(title: "App Dev", attendees: ["Katie", "Gray", "Euna", "Luis", "Darla"], lengthInMinutes: 5, color: Color("App Dev")),
            DailyScrum(title: "Web Dev", attendees: ["Chella", "Chris", "Christina", "Eden", "Karla", "Lindsey", "Aga", "Chad", "Jenn", "Sarah"], lengthInMinutes: 1, color: Color("Web Dev"))
        ]
    }
}
