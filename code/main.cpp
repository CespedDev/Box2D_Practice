//
// Carlos Cabrera Fernández
// 2016.04+
//

#include <memory>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Utils.hpp"
#include "Scene.hpp"
#include "InputSystem.hpp"

using namespace sf;
using namespace std;

using namespace GameBox2D;

namespace
{
    void render (b2World & physics_world, RenderWindow & window, float scale)
    {
        // Se cachea el alto de la ventana en una variable local:

        float window_height = (float)window.getSize ().y;

        // Se recorre toda la lista de bodies de physics_world:

        for (b2Body * body = physics_world.GetBodyList (); body != nullptr; body = body->GetNext ())
        {
            // Se obtiene el transform del body:

            const b2Transform & box2d_transform = body->GetTransform ();

            // Se recorre la lista de fixtures del body:

            for (b2Fixture * fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext ())
            {
                // Se obtiene el tipo de forma de la fixture:

                b2Shape::Type shape_type = fixture->GetShape ()->GetType ();

                if (shape_type == b2Shape::e_circle)
                {
                    // Se crea un CircleShape a partir de los atributos de la forma de la fixture y del body:

                    b2CircleShape * box2d_circle = dynamic_cast< b2CircleShape * >(fixture->GetShape ());
                    CircleShape      sfml_circle;

                    sfml_circle.setFillColor (Color::Blue);
                    sfml_circle.setRadius    (box2d_circle->m_radius);

                    // Se establece el transform del círculo de SFML (posición y escala) según el transform de
                    // física y la escala de física a gráficos (de metros a pixels):

                    // En SFML la posición del círculo se establece en relación a la esquina superior izquierda
                    // del cuadrado en el que está inscrito y por eso a su posición se le resta el radio.

                    b2Vec2 box2d_circle_center_position = b2Mul (box2d_transform, box2d_circle->m_p);

                    sfml_circle.setPosition 
                    ({
                                        (box2d_circle_center_position.x - box2d_circle->m_radius) * scale, 
                        window_height - (box2d_circle_center_position.y + box2d_circle->m_radius) * scale
                    });

                    sfml_circle.setScale (scale, scale);

                    window.draw (sfml_circle);
                }
                else
                if (shape_type == b2Shape::e_edge)
                {
                    // Se toman los dos vértices del segmento y se ajusta su posición usando el transform del body.
                    // Los vértices resultantes se convierten y se ponen en un array para finalmente dibujar el segmento
                    // que los une usando la sobrecarga del método draw() que permite dibujar primitivas de OpenGL a
                    // partir de datos de vértices.

                    b2EdgeShape * box2d_edge = dynamic_cast< b2EdgeShape * >(fixture->GetShape ());

                    b2Vec2  box2d_edge_start = b2Mul (box2d_transform, box2d_edge->m_vertex1);
                    b2Vec2  box2d_edge_end   = b2Mul (box2d_transform, box2d_edge->m_vertex2);

                    Vertex line[] =
                    {
                        Vertex({ box2d_edge_start.x * scale, window_height - box2d_edge_start.y * scale }, Color::Green),
                        Vertex({ box2d_edge_end  .x * scale, window_height - box2d_edge_end  .y * scale }, Color::Green),
                    };

                    window.draw (line, 2, Lines);
                }
                else
                if (shape_type == b2Shape::e_polygon)
                {
                    // Se toma la forma poligonal de Box2D (que siempre es convexa) y se crea a partir de sus vértices un
                    // ConvexShape de SFML. Este proceso no hay por qué repetirlo cada vez ya que no depende del transform.

                    b2PolygonShape * box2d_polygon = dynamic_cast< b2PolygonShape * >(fixture->GetShape ());
                    ConvexShape       sfml_polygon;

                    int number_of_vertices = box2d_polygon->m_count;

                    sfml_polygon.setPointCount (number_of_vertices);
                    sfml_polygon.setFillColor  (Color::Yellow);

                    for (int index = 0; index < number_of_vertices; index++)
                    {
                        sfml_polygon.setPoint
                        (
                            index, 
                            { box2d_polygon->m_vertices[index].x, - box2d_polygon->m_vertices[index].y }

                            // ADVERTENCIA: la y anterior estaba positiva, y dibuja al reves la figuras. El positivo sfml
                            // no es el mismo que el de box2D por eso hay que darle la vuelta.
                        );
                    }

                    // Se establece el transform del polígono de SMFL (posición, rotación y escala):

                    sfml_polygon.setPosition (sf::Vector2f{ box2d_transform.p.x * scale, window_height - box2d_transform.p.y * scale });
                    sfml_polygon.setRotation (-box2d_transform.q.GetAngle () * 180.f / 3.14159265f);    // Se pasa de radianes a grados
                    sfml_polygon.setScale    (scale, scale);

                    window.draw (sfml_polygon);
                }
            }
        }
    }
}

int main ()
{
    RenderWindow window(VideoMode(1500, 540), "Box2D Intro", Style::Titlebar | Style::Close, ContextSettings(32));
    window.setVerticalSyncEnabled (true);
    
    unique_ptr<Scene> scene { new Scene(Vec2(0, -10), 100.f)};
    scene->Start();

    unique_ptr<InputSystem> inputSystem{ new InputSystem(scene->GetEventSystem(), window) };

    const float target_fps  = 60.f;                     // Cuántos fotogramas por segundo se busca conseguir
    const float target_time = 1.f / target_fps;         // Duración en segundos de un fotograma a la tasa deseada
    
    float delta_time = target_time;                     // Previsión de la duración del fotograma actual

    Clock timer;

    do
    {
        timer.restart ();

        // Update:
        inputSystem->Update();
        scene      ->Update(delta_time);

        // Render:
        window.clear ();
        render (scene->GetWorld(), window, scene->physics_to_graphics_scale);
        window.display ();



        // Si resulta necesario se detiene la ejecución unos instantes para no exceder la tasa de
        // fotogramas por segundo deseada:

        float elapsed = timer.getElapsedTime ().asSeconds ();

        if (elapsed < target_time)
        {
            sleep (seconds (target_time - elapsed));
        }

        // Se restablece la estimación de la duración del siguiente fotograma:

        delta_time = timer.getElapsedTime ().asSeconds ();
    }
    while (scene->running);

    return EXIT_SUCCESS;
}
