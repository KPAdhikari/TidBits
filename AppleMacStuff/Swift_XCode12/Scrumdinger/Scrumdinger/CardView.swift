//
//  CardView.swift
//  Scrumdinger
//
//  Created by Krishna Adhikari on 8/10/21.
//

//import Foundation
import SwiftUI

struct CardView: View {
    let scrum: DailyScrum
    var body: some View {
        //Text("Hello, World")
        VStack(alignment: .leading) {
            Text(scrum.title)
                .font(.headline)
            Spacer()
            HStack {
                Label("\(scrum.attendees.count)", systemImage: "person.3")
                    .accessibilityElement(children: /*@START_MENU_TOKEN@*/.ignore/*@END_MENU_TOKEN@*/)
                    .accessibilityLabel(Text("Attendees"))
                    .accessibilityValue(Text("\(scrum.attendees.count)"))
                Spacer()
                Label("\(scrum.lengthInMinutes)", systemImage: "clock")
                    .padding(.trailing, 20)
                    .accessibilityElement(children: /*@START_MENU_TOKEN@*/.ignore/*@END_MENU_TOKEN@*/)
                    .accessibilityLabel(Text("Meeting length"))
                    .accessibilityValue(Text("\(scrum.lengthInMinutes) minutes"))
            }
            .font(.caption)
        }
        .padding()
        //.foregroundColor(scrum.color.accessibleFontColor) //kp: For some Color+Codable.swift's color is giving me all white color
        .foregroundColor(.blue)//(Color(UIColor.systemTeal))//(.red)
        .background(Color(UIColor.systemGray4)) //My own color
    }
}

struct CardView_Previews: PreviewProvider {
    static var scrum = DailyScrum.data[0]
    static var previews: some View {
        CardView(scrum: scrum)
            .background(scrum.color)
            .previewLayout(.fixed(width: 400, height: 60))
    }
}