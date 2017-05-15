#include <iterator>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

#include "imdb.h"


IMDb::IMDb() {
    // initialize what you need here.
}

IMDb::~IMDb() {}

void IMDb::add_movie(std::string movie_name,
                     std::string movie_id,
                     int timestamp, // unix timestamp when movie was launched
                     std::vector<std::string> categories,
                     std::string director_name,
                     std::vector<std::string> actor_ids) {

    movie m(movie_name, movie_id, timestamp, categories, director_name,
            actor_ids);
    std::pair<std::string, movie> elem(movie_id, m);
    movies.insert(elem);

    auto found_director = directors_influence.find(director_name);
    director dir(director_name);

    if (found_director != multimap::end) {
        dir = found_director->second;
        directors_influence.erase(found_director);
    }

    for (i = 0; i < actor_ids.size(); ++i) {
        // Trebuia actors[actor_ids[i]]
        // Am refacut structura la clasa si am facut getters
        actor &current_actor = actors[actor_ids[i]];
        int &debut_year = current_actor.get_debut_year();
        int &last_year = current_actor.get_last_year();
        int &years = current_actor.get_years();

        if (debut_year > timestamp) {
            debut_year = timestamp;
        }

        if (last_year < timestamp) {
            last_year = timestamp;
        }

        years = last_year - debut_year;
        auto found_actor = actors_career.find(current_actor);

        if (found_actor != set::end) {
            // Daca actorul este deja in ABC, il sterg si il adaug din nou
            // cu noul numar de ani
            actors_career.erase(found);
        }
        // Adaug actorul in ABC acum ca a participat in cel putin un film
        actors_career.insert(current_actor);

        if (!dir.check_collaboration(actor_ids[i])) {
            dir.add_collaboration(actor_ids[i]);
        }
    }

    directors_influence.emplace(director_name, dir);
}

void IMDb::add_user(std::string user_id, std::string name) {
    // Vezi ca ai overload pe operatorul [] care iti creaza elementul
    // daca el deja nu exista, e mai usor asa.
    std::pair<std::string, std::string> user(user_id, name);
    users.insert(user);
}

void IMDb::add_actor(std::string actor_id, std::string name) {
    // Idem add_user
    actor new_actor(actor_id, name);
    std::pair<std::string, actor> elem(actor_id, new_actor);
    actors.insert(elem);
}

void IMDb::add_rating(std::string user_id, std::string movie_id, int rating) {
    if (movies.find(movie_id) != std::unordered_map::end) {
        movies[movie_id].add_rating(user_id, rating);
    }
}

void IMDb::update_rating(std::string user_id, std::string movie_id, int rating) {
    if (movies.find(movie_id) != std::unordered_map::end) {
        movies[movie_id].update_rating(user_id, rating);
    }
}

void IMDb::remove_rating(std::string user_id, std::string movie_id) {
    if (movies.find(movie_id) != std::unordered_map::end) {
        movies[movie_id].remove_rating(user_id, rating);
    }
}

std::string IMDb::get_rating(std::string movie_id) {
    // Am pus conditia de fara rating la inceput
    // Nu ai tratat cazul de rotunjire pt %10 < 5
    // Am scos operatiile ce se repeta din if
    if (movies.find(movie_id) != std::unordered_map::end) {
        if (movies[movie_id].no_rating()) {
            return NONE;
        }

        double rating;
        std::string final_rating;
        int temp_rating = (int)(movies[movie_id].get_rating() * 1000);

        if (temp_rating % 10 >= 5) {
            temp_rating += 10;
        }

        temp_rating /= 10;
        rating = (double)temp_rating / 100.0;
        final_rating = to_string(rating);
        return final_rating;
    }
}

std::string IMDb::get_longest_career_actor() {
    if (!actors_career.empty()) {
        auto iter = actors_career.rend();
        actor current_actor = *(--iter);

        return current_actor.actor_id;
    }
    return NONE;
}

std::string IMDb::get_most_influential_director() {
    if (!directors_influence.empty()) {
        auto iter = actors_career.rend();
        std::string name = (--iter)->director_name;

        return name;
    }
    return NONE;
}

std::string IMDb::get_best_year_for_category(std::string category) {
    return "";
}

std::string IMDb::get_2nd_degree_colleagues(std::string actor_id) {
    return "";
}

std::string IMDb::get_top_k_most_recent_movies(int k) {
    return "";
}

std::string IMDb::get_top_k_actor_pairs(int k) {
    return "";
}

std::string IMDb::get_top_k_partners_for_actor(int k, std::string actor_id) {
    return "";
}

std::string IMDb::get_top_k_most_popular_movies(int k) {
    return "";
}

std::string IMDb::get_avg_rating_in_range(int start, int end) {
    return "";
}
