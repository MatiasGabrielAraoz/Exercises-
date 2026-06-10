import ollama

def debate(tema, iteraciones=3):
    modelo_a = "gemma4:latest"  # Puedes usar modelos distintos si quieres
    modelo_b = "gemma4:latest"
    
    # Propuesta inicial
    print(f"--- Iniciando debate sobre: {tema} ---")
    respuesta = ollama.generate(model=modelo_a, prompt=f"Presenta una solución técnica detallada para: {tema}")['response']
    
    for i in range(iteraciones):
        print(f"\n--- Ronda {i+1} ---")
        
        # El Crítico analiza
        critica = ollama.generate(model=modelo_b, prompt=f"Actúa como un experto crítico. Encuentra fallos, riesgos o puntos débiles en esta propuesta: {respuesta}")['response']
        print(f"Crítica de {modelo_b}: {critica[:500]}...") # Solo mostramos el inicio
        
        # El Proponente defiende o mejora
        respuesta = ollama.generate(model=modelo_a, prompt=f"Basado en esta crítica: {critica}, mejora y redefine tu propuesta inicial: {tema}")['response']
        print(f"Respuesta mejorada de {modelo_a} lista.")

    print("\n--- Resultado Final ---")
    print(respuesta)

debate("Simula un debate entre dos expertos en relaciones y comunicación social para aconsejar a un chico que le enseña programación a una chica de 17 años (un par de años mayor que él). A él le gusta ella. Experto A (El Intrépido): Propone formas de escalar la relación, usar analogías de programación para flirtear de forma sutil y cómo pasar de las clases a algo más personal. Experto B (El Prudente): Advierte sobre los riesgos de arruinar la dinámica de enseñanza, la diferencia de edad (aunque sea pequeña, a los 17 se nota) y cómo leer las señales antes de actuar. Consigna: Debatan 3 rondas sobre: Cómo detectar si el interés es mutuo durante las explicaciones de código. Una estrategia para invitarla a salir sin que sea incómodo si dice que no. El balance entre ser su 'profesor' y ser un pretendiente interesado. Al final, den un plan de acción con pasos concretos")
