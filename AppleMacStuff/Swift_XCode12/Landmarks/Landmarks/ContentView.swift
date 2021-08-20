//
//  ContentView.swift
//  Landmarks
//
//  Created by Krishna Adhikari on 8/13/21.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        VStack(alignment: .leading) {
            //Text("Hello, world!")
            Text("Turtle Rock!")
                .font(.title)
                //.foregroundColor(Color.green)
                .foregroundColor(.green) //kp: Samething as above?
                //.padding()
            HStack {
                Text("Joshua Tree National Park")
                    .font(.subheadline)
                Spacer()
                Text("California")
                    .font(.subheadline)
            }
        }
        .padding()
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
