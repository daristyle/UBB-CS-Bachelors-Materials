/*#include "Tests.h"
#include "Service.h"
#include "Tutorial.h"
#include <cassert>
#include <iostream>

void testDuration() {
    Duration d{10, 70};
    assert(d.get_minutes() == 11);
    assert(d.get_seconds() == 10);

    d.set_minutes(5);
    assert(d.get_minutes() == 5);

    d.set_seconds(130);
    assert(d.get_minutes() == 7);
    assert(d.get_seconds() == 10);

    assert(d.to_string() == "7:10");

    Duration d2{7, 10};
    assert(d == d2);
    
    Duration d3{7, 11};
    assert(!(d == d3));
    
    Duration d4{8, 10};
    assert(!(d == d4));
    
    Duration d5{0, 0};
    assert(d5.get_minutes() == 0);
    assert(d5.get_seconds() == 0);
    
    d5.set_seconds(30);
    assert(d5.get_seconds() == 30);
    assert(d5.get_minutes() == 0);
}

void testTutorial() {
    Tutorial t1;
    assert(t1.get_title() == "");
    assert(t1.get_presenter() == "");
    assert(t1.get_likes() == 0);
    assert(t1.get_url() == "");
    assert(t1.get_duration() == Duration(0, 0));

    Tutorial t2{"Title", "Presenter", {10, 20}, 100, "url"};
    assert(t2.get_title() == "Title");
    assert(t2.get_presenter() == "Presenter");
    assert(t2.get_duration() == Duration(10, 20));
    assert(t2.get_likes() == 100);
    assert(t2.get_url() == "url");

    t2.set_title("NewTitle");
    assert(t2.get_title() == "NewTitle");
    t2.set_presenter("NewPresenter");
    assert(t2.get_presenter() == "NewPresenter");
    t2.set_duration({1, 1});
    assert(t2.get_duration() == Duration(1, 1));
    t2.set_likes(200);
    assert(t2.get_likes() == 200);
    t2.set_url("new_url");
    assert(t2.get_url() == "new_url");

    std::string str = t2.to_string();
    assert(str.find("NewTitle") != std::string::npos);
    assert(str.find("NewPresenter") != std::string::npos);
    assert(str.find("new_url") != std::string::npos);
    assert(str.find("200") != std::string::npos);
    
    t2.like();
    assert(t2.get_likes() == 201);

    Tutorial t3{"NewTitle", "NewPresenter", {0, 0}, 0, ""};
    assert(t2 == t3);
    
    Tutorial t4{"DiffTitle", "NewPresenter", {1, 1}, 200, "new_url"};
    assert(!(t2 == t4));
    
    Tutorial t5{"NewTitle", "DiffPresenter", {1, 1}, 200, "new_url"};
    assert(!(t2 == t5));
}

/*void testVector() {
    vector<int> v(2);
    assert(v.size() == 0);
    assert(v.empty());

    v.push_back(1);
    v.push_back(2);
    assert(v.size() == 2);
    assert(!v.empty());
    assert(v.back() == 2);
    assert(v[0] == 1);
    assert(v[1] == 2);

    v.push_back(3);
    assert(v.size() == 3);
    assert(v[2] == 3);

    v.pop_back();
    assert(v.size() == 2);
    v.pop_back();
    v.pop_back();
    assert(v.empty());

    try {
        v.back();
        assert(false);
    } catch (std::out_of_range&) {
        assert(true);
    }

    vector<int> v2 = v;
    assert(v2.empty());
    
    v2.push_back(10);
    vector<int> v3 = v2;
    assert(v3.size() == 1);
    assert(v3[0] == 10);
    
    vector<int> v4(16);
    v4.push_back(1);
    v4.push_back(2);
    v4.push_back(3);
    v4.push_back(4);
    v4.push_back(5);
    v4.pop_back();
    v4.pop_back();
    v4.pop_back();
    v4.pop_back();
    assert(v4.size() == 1);
    assert(v4[0] == 1);
    
    vector<int> v5;
    assert(v5.size() == 0);
    v5.push_back(100);
    assert(v5[0] == 100);
    
    vector<Tutorial> vt;
    Tutorial tut{"T", "P", {1,1}, 1, "U"};
    vt.push_back(tut);
    assert(vt.size() == 1);
    assert(vt[0].get_title() == "T");
    
    vector<Tutorial> vt2 = vt;
    assert(vt2.size() == 1);
    assert(vt2[0].get_title() == "T");
    
    vector<int> v6(1);
    for(int i = 0; i < 20; i++) {
        v6.push_back(i);
    }
    assert(v6.size() == 20);
    for(int i = 0; i < 20; i++) {
        assert(v6[i] == i);
    }
}*/

/*void testRepository() {
    MemoryRepository repo{};
    assert(repo.getAll().size() == 0);
    
    Tutorial t{"T", "P", {1,1}, 1, "U"};
    assert(repo.add(t));
    assert(!repo.add(t));
    assert(repo.getAll().size() == 1);

    assert(repo.find(t) == 0);
    Tutorial t2{"T2", "P2", {2,2}, 2, "U2"};
    assert(repo.find(t2) == -1);

    assert(!repo.remove(t2));
    
    assert(!repo.update(t2));

    t.set_likes(10);
    assert(repo.update(t));
    assert(repo.getAll()[0].get_likes() == 10);

    repo.likeTutorial(t);
    assert(repo.getAll()[0].get_likes() == 11);
    
    repo.likeTutorial(t2);

    assert(repo.remove(t));
    assert(repo.getAll().size() == 0);
    
    MemoryRepository repo3{};
    Tutorial ta{"A", "PA", {1,1}, 1, "UA"};
    Tutorial tb{"B", "PB", {2,2}, 2, "UB"};
    Tutorial tc{"C", "PC", {3,3}, 3, "UC"};
    repo3.add(ta);
    repo3.add(tb);
    repo3.add(tc);
    assert(repo3.getAll().size() == 3);
    assert(repo3.remove(ta));
    assert(repo3.getAll().size() == 2);
    assert(repo3.find(ta) == -1);

    MemoryRepository repo2{};
    assert(repo2.getAll().size() == 0);
}

void testService() {
    Service serv;
    
    assert(serv.getAllFromRepo().size() == 0);
    
    Tutorial t{"T", "P", {1,1}, 1, "U"};
    assert(serv.addToRepo(t));
    assert(!serv.addToRepo(t));
    assert(serv.getAllFromRepo().size() == 1);

    Tutorial t2{"T2", "P", {2,2}, 2, "U2"};
    serv.addToRepo(t2);
    auto p = serv.getPresentedBy("P");
    assert(p.size() == 2);
    
    auto p2 = serv.getPresentedBy("NonExistent");
    assert(p2.size() == 0);
    
    auto p3 = serv.getPresentedBy("Bejan");
    assert(p3.size() == 0);

    t.set_likes(999);
    assert(serv.updateInRepo(t));
    
    assert(serv.removeFromRepo(t));
    assert(!serv.removeFromRepo(t));

    assert(serv.getWatchlist().size() == 0);
    assert(serv.addToWatchlist(t2));
    assert(!serv.addToWatchlist(t2));
    assert(serv.getWatchlist().size() == 1);
    assert(serv.removeFromWatchlist(t2));
    assert(serv.getWatchlist().size() == 0);
    assert(!serv.removeFromWatchlist(t2));

    serv.likeTutorial(t2);
    
    Tutorial t3{"NonExistent", "NE", {0,0}, 0, ""};
    assert(!serv.updateInRepo(t3));
}

void testAll(){
    testDuration();
    testTutorial();
    //testVector();
    testRepository();
    testService();
    std::cout << "All tests passed!" << std::endl;
}*/
