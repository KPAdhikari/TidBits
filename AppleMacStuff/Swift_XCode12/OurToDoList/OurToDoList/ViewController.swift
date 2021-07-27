//
//  ViewController.swift
//  OurToDoList
//
//  Created by Krishna Adhikari on 7/24/21.
//

import UIKit

class ViewController: UIViewController, UITableViewDataSource {
    
    private let table: UITableView = {
       let table = UITableView()
        table.register(UITableViewCell.self,
                       forCellReuseIdentifier: "cell")
        return table
    }()
    
    var items = [String]() //kp: Array of strings
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.items = UserDefaults.standard.stringArray(forKey: "items") ?? []
        // Do any additional setup after loading the view.
        title = "To Do List"
        view.addSubview(table)
        table.dataSource = self
        navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .add,
                                                            target: self,
                                                            action: #selector(didTapAdd))
    }
    
    @objc private func didTapAdd() {
        let alert = UIAlertController(title: "New Item", message: "Enter new to do list item!",
                                      preferredStyle: .alert)
        alert.addTextField { field in
            field.placeholder = "Enter item ..."
        }
        alert.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
        alert.addAction(UIAlertAction(title: "Done", style: .default, handler: { [weak self] //[weak self] to avoid memory leak
            (_) in
            if let field = alert.textFields?.first {
                if let text = field.text, !text.isEmpty {
                    // Enter new to do list item
                    ///print(text) //kp: it printed only on the console of the IDE not the app's screen
                    ///self.items.append(text)
                    ///self.table.reloadData()
                    //Making sure above lines run in the main thread
                    DispatchQueue.main.async {
                        //==== Without these the previous list disappeared when app was restarted ===
                        var currentItems = UserDefaults.standard.stringArray(forKey: "items") ?? []
                        //let newEntry = [text] //An array of 'text'
                        currentItems.append(text)
                        //UserDefaults.standard.setValue(newEntry, forKey: "items")
                        UserDefaults.standard.setValue(currentItems, forKey: "items")
                        //=========
                        self?.items.append(text) //Question mark makes it optional?
                        self?.table.reloadData()
                    }
                }
            }
        }))
        present(alert, animated: true)
    }
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        table.frame = view.bounds
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        //return 0
        return items.count //Show the # of items we have instead of just 0.
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "cell",
                                                 for: indexPath)
        cell.textLabel?.text = items[indexPath.row]
        return cell
    }
}

