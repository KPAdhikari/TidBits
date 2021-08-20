//
//  Weather.swift
//  Weather
//
//  Created by Krishna Adhikari on 8/17/21.
//  kp: This will be our model

import Foundation

public struct Weather {
    let city: String
    let temperature: String
    let description: String
    let iconName: String
    
    init(response: APIResponse) {
        city = response.name
        temperature = "\(Int(response.main.temp))"
        //response.weather is a list, so we're using 'first' element below
        //Since this is optional, we have ?? and we provide an empty string "" as
        // default value after '??' below
        description = response.weather.first?.description ?? ""
        iconName = response.weather.first?.iconName ?? ""
    }
}
