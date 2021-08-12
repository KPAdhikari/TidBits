//
//  ScrumsView.swift .swift
//  Scrumdinger
//
//  Created by Krishna Adhikari on 8/11/21.
//
// Source: https://developer.apple.com/tutorials/app-dev-training/displaying-data-in-a-list

import SwiftUI

struct ScrumsView: View {
    let scrums: [DailyScrum]

    var body: some View {
        //Text("Hello, World!")
        //kp: List view
        List {
            //kp: ForEach view
            //ForEach(scrums, id: \.title) { scrum in
            ForEach(scrums) { scrum in
                CardView(scrum: scrum)
                    .listRowBackground(scrum.color)
            }
        }
    }
}


struct ScrumsView_Previews: PreviewProvider {
    static var previews: some View {
        ScrumsView(scrums: DailyScrum.data)
    }
}
